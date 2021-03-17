#ifndef UNIT_TEST // disable program main loop while unit testing in progress

#include <Arduino.h>
#include <avr/sleep.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include "config.h"

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = ETHERNET_MAC;
String ip = "";
const char *broker = MQTT_BROKER;
EthernetClient ethClient;
PubSubClient mqttClient;

typedef struct
{
  boolean applied;
  uint8_t counter;
  uint8_t outPin;
} DoorBell;

DoorBell doorBells[NUM_DOORBELLS];

void isrDoorBell1()
{
  doorBells[0].applied = true;
}

void isrDoorBell2()
{
  doorBells[1].applied = true;
}

void isrDoorBell3()
{
  doorBells[2].applied = true;
}

void isrDoorBell4()
{
  doorBells[3].applied = true;
}

/**
 * Safe power when nothing to do
 */
void enterSleep(void)
{
  for (uint8_t i = 0; i < NUM_DOORBELLS; i++)
  {
    digitalWrite(doorBells[i].outPin, LOW);
  }

  digitalWrite(LED_BUILTIN, LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  /* Sleeping now, execution will continue here in case of wakeup event. */
  sleep_disable();
  digitalWrite(LED_BUILTIN, HIGH);
}

/**
 * Executed once after reset
 */
void setup()
{
#ifdef OUTPUT_B1
  doorBells[0].outPin = OUTPUT_B1;
#endif
#ifdef OUTPUT_B2
  doorBells[1].outPin = OUTPUT_B2;
#endif
#ifdef OUTPUT_B3
  doorBells[2].outPin = OUTPUT_B3;
#endif
#ifdef OUTPUT_B4
  doorBells[3].outPin = OUTPUT_B4;
#endif

  // configure LEDs
  pinMode(LED_BUILTIN, OUTPUT);
  for (uint8_t i = 0; i < NUM_DOORBELLS; i++)
  {
    pinMode(doorBells[i].outPin, OUTPUT);
    digitalWrite(doorBells[i].outPin, LOW);
  }

// configure buttons
#ifdef INPUT_B1
  pinMode(INPUT_B1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INPUT_B1), isrDoorBell1, FALLING);
#endif
#ifdef INPUT_B2
  pinMode(INPUT_B2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INPUT_B2), isrDoorBell2, FALLING);
#endif
#ifdef INPUT_B3
  pinMode(INPUT_B3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INPUT_B3), isrDoorBell3, FALLING);
#endif
#ifdef INPUT_B4
  pinMode(INPUT_B4, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INPUT_B4), isrDoorBell4, FALLING);
#endif

  for (uint8_t i = 0; i < NUM_DOORBELLS; i++)
  {
    doorBells[i].applied = false;
    doorBells[i].counter = 0;
  }

  Serial.begin(9600);
  while (!Serial)
  {
  };
  Serial.println(F("xxthunder/DoorBell"));
  Serial.println();

  // configure ethernet using DHCP
  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("Failed to configure Ethernet using DHCP");
    // connection fails, stop program run.
    for (;;)
      ;
  }

  Serial.println(F("Ethernet configured via DHCP"));
  Serial.print("IP address: ");
  Serial.println(Ethernet.localIP());
  Serial.println();

  ip = String(Ethernet.localIP()[0]);
  ip = ip + ".";
  ip = ip + String(Ethernet.localIP()[1]);
  ip = ip + ".";
  ip = ip + String(Ethernet.localIP()[2]);
  ip = ip + ".";
  ip = ip + String(Ethernet.localIP()[3]);

  // setup mqtt client
  mqttClient.setClient(ethClient);
  mqttClient.setServer(broker, 1883);
  if (mqttClient.connect(MQTT_ID))
  {
    Serial.println("Connection has been established, well done");
    mqttClient.publish(MQTT_ID "/ip", ip.c_str());
  }
  else
  {
    Serial.println("Looks like the server connection failed...");
  }
}

void handleButtonEvents()
{
  for (uint8_t i = 0; i < NUM_DOORBELLS; i++)
  {
    char topic[11];
    sprintf(topic, "DoorBell/b%d", i + 1);
    if (doorBells[i].applied)
    {
      mqttClient.publish(topic, "ON");
      digitalWrite(doorBells[i].outPin, HIGH);
      doorBells[i].applied = false;
      doorBells[i].counter = LOOP_CNT_APPLIED;
    }
    else
    {
      if (doorBells[i].counter > 0)
      {
        doorBells[i].counter--;
      }
      else
      {
        mqttClient.publish(topic, "OFF");
        digitalWrite(doorBells[i].outPin, LOW);
        doorBells[i].counter = LOOP_CNT_IDLE;
      }
    }
  }
}

void loop()
{
  handleButtonEvents();
  if (!mqttClient.connected())
    mqttClient.connect(MQTT_ID);
  mqttClient.loop();
  delay(LOOP_TIME_MS);
  //enterSleep();
}

#endif
