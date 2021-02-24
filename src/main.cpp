#ifndef UNIT_TEST // disable program main loop while unit testing in progress

#include <Arduino.h>
#include <avr/sleep.h>
#include <SPI.h>
#include <Ethernet.h>
#include <MD5.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

// connected buttons
#define INPUT_BUTTON1 PIND2
#define INPUT_BUTTON2 PIND3

// connected leds
#define OUTPUT_LED1 8
#define OUTPUT_LED2 9

boolean BUTTON1_APPLIED;
boolean BUTTON2_APPLIED;

/**
 * Interrupt service routine for the first door bell
 */
void isrBell1()
{
  BUTTON1_APPLIED = true;
}

/**
 * Interrupt service routine for the second door bell
 */
void isrBell2()
{
  BUTTON2_APPLIED = true;
}

/**
 * Safe power when nothing to do
 */
void enterSleep(void)
{
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(OUTPUT_LED1, LOW);
  digitalWrite(OUTPUT_LED2, LOW);
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
  // configure LEDs
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(OUTPUT_LED1, OUTPUT);
  digitalWrite(OUTPUT_LED1, LOW);
  pinMode(OUTPUT_LED2, OUTPUT);
  digitalWrite(OUTPUT_LED2, LOW);

  // configure buttons
  pinMode(INPUT_BUTTON1, INPUT_PULLUP);
  pinMode(INPUT_BUTTON2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INPUT_BUTTON1), isrBell1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(INPUT_BUTTON2), isrBell2, CHANGE);
  //delay(5000);
  BUTTON1_APPLIED = false;
  BUTTON2_APPLIED = false;

  // configure ethernet
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("Failed to configure Ethernet using DHCP");
    // connection fails, stop program run.
    for (;;)
      ;
  }

  // print out your local IP address
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++)
  {
    // print out four byte IP address
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }

  Serial.println();
}

void handleButtonEvents()
{
  digitalWrite(OUTPUT_LED1, BUTTON1_APPLIED ? HIGH : LOW);
  digitalWrite(OUTPUT_LED2, BUTTON2_APPLIED ? HIGH : LOW);
  BUTTON1_APPLIED = false;
  BUTTON2_APPLIED = false;
}

void loop()
{
  handleButtonEvents();
  delay(5000);
  //enterSleep();
}

#endif