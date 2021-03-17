#include "test_mqtt.h"

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();

    RUN_TEST(tc__mqttclient);

    UNITY_END();

    pinMode(OUTPUT_B1, OUTPUT);
    digitalWrite(OUTPUT_B1, LOW);
}

void loop()
{
    digitalWrite(OUTPUT_B1, HIGH);
    delay(100);
    digitalWrite(OUTPUT_B1, LOW);
    delay(500);
}
