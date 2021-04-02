#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Loop delay/time
#define LOOP_TIME_MS 1000
#define LOOP_CNT_IDLE 30
#define LOOP_CNT_APPLIED 5

// connected door bell buttons and status leds
#define NUM_DOORBELLS 2
#define INPUT_B1 PIND2
#define INPUT_B2 PIND3
#define OUTPUT_B1 8
#define OUTPUT_B2 9

#define ETHERNET_MAC                       \
    {                                      \
        0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED \
    }

#define MQTT_BROKER "<your broker ip or hostname>"
#define MQTT_ID "DoorBell"
#define MQTT_USER "***"
#define MQTT_PASSWD "***"

#endif
