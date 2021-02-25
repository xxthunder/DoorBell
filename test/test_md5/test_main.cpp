#include "test_md5.h"
#include "test_md5builder.h"

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

    RUN_TEST(tc__MD5__empty_string);
    RUN_TEST(tc__MD5__hello_world);
    RUN_TEST(tc__MD5__hello_another_string);

    RUN_TEST(tc__MD5builder__empty_string);
    RUN_TEST(tc__MD5builder__hello_world);
    RUN_TEST(tc__MD5builder__another_string);

    UNITY_END();
}

void loop()
{
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}
