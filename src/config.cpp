#include "config.h"

void configure()
{
    // configure LEDs
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(OUTPUT_LED1, OUTPUT);
    digitalWrite(OUTPUT_LED1, LOW);
    pinMode(OUTPUT_LED2, OUTPUT);
    digitalWrite(OUTPUT_LED2, LOW);
}
