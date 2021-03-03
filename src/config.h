#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// connected buttons
#define INPUT_BUTTON1 PIND2
#define INPUT_BUTTON2 PIND3

// connected leds
#define OUTPUT_LED1 8
#define OUTPUT_LED2 9

#define ETHERNET_MAC                       \
    {                                      \
        0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED \
    }

void configure();

#endif
