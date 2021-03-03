#include "test_httpclient.h"

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

    RUN_TEST(tc__HttpClient__SimpleHttp);
    RUN_TEST(tc__HttpClient__FritzBox_connect);

    UNITY_END();

    configure();
}

void loop()
{
    digitalWrite(OUTPUT_LED1, HIGH);
    delay(100);
    digitalWrite(OUTPUT_LED1, LOW);
    delay(500);
}
