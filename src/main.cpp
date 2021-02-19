#include <Arduino.h>
#include <avr/sleep.h>

// external interrupts
#define INPUT_BUTTON_BELL1 PIND2
#define INPUT_BUTTON_BELL2 PIND3

// Indicator leds for applied buttons
#define OUTPUT_LED_BELL1 8
#define OUTPUT_LED_BELL2 9

boolean BUTTON_BELL1_APPLIED;
boolean BUTTON_BELL2_APPLIED;

/**
 * Interrupt service routine for the first door bell
 */
void isrBell1()
{
  BUTTON_BELL1_APPLIED = true;
}

/**
 * Interrupt service routine for the second door bell
 */
void isrBell2()
{
  BUTTON_BELL2_APPLIED = true;
}

/**
 * Safe power when nothing to do
 */
void enterSleep(void)
{
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(OUTPUT_LED_BELL1, LOW);
  digitalWrite(OUTPUT_LED_BELL2, LOW);
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
  pinMode(OUTPUT_LED_BELL1, OUTPUT);
  digitalWrite(OUTPUT_LED_BELL1, LOW);
  pinMode(OUTPUT_LED_BELL2, OUTPUT);
  digitalWrite(OUTPUT_LED_BELL2, LOW);

  // configure buttons
  pinMode(INPUT_BUTTON_BELL1, INPUT_PULLUP);
  pinMode(INPUT_BUTTON_BELL2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INPUT_BUTTON_BELL1), isrBell1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(INPUT_BUTTON_BELL2), isrBell2, CHANGE);
  delay(5000);
  BUTTON_BELL1_APPLIED = false;
  BUTTON_BELL2_APPLIED = false;
}

void loop()
{
  digitalWrite(OUTPUT_LED_BELL1, BUTTON_BELL1_APPLIED ? HIGH : LOW);
  digitalWrite(OUTPUT_LED_BELL2, BUTTON_BELL2_APPLIED ? HIGH : LOW);
  delay(5000);
  BUTTON_BELL1_APPLIED = false;
  BUTTON_BELL2_APPLIED = false;
  enterSleep();
}
