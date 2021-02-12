#include <Arduino.h>

#define PIN_BUTTON_BELL1 PIND2
#define PIN_BUTTON_BELL2 PIND3

#define PIN_BELL1 8
#define PIN_BELL2 9

void bell1()
{
  digitalWrite(PIN_BELL1, HIGH);
}

void bell2()
{
  digitalWrite(PIN_BELL2, HIGH);
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(PIN_BUTTON_BELL1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_BELL1), bell1, RISING);
  pinMode(PIN_BUTTON_BELL2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_BELL2), bell2, RISING);

  pinMode(PIN_BELL1, OUTPUT);
  digitalWrite(PIN_BELL1, LOW);
  pinMode(PIN_BELL2, OUTPUT);
  digitalWrite(PIN_BELL2, LOW);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
}
