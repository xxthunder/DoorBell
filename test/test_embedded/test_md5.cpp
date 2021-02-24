#include <Arduino.h>
#include <MD5.h>
#include "unity.h"

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

char *md5_calc(char const *input)
{
    //generate the MD5 hash for our string
    unsigned char *hash = MD5::make_hash((char *)input);
    //generate the digest (hex encoding) of our hash
    char *md5str = MD5::make_digest(hash, 16);
    free(hash);
    return (md5str);
}

void test_function_md5_hello_world(void)
{
    char *md5str = md5_calc("hello world");
    TEST_ASSERT_EQUAL_CHAR_ARRAY("5eb63bbbe01eeed093cb22bb8f5acdc3", md5str, sizeof(md5str));
    free(md5str);
}

void test_function_md5_hello_another_string(void)
{
    char *md5str = md5_calc("Another string we would like to test.");
    TEST_ASSERT_EQUAL_CHAR_ARRAY("ee03459c0cd21889a9f383ba51cfa05e", md5str, sizeof(md5str));
    free(md5str);
}

void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_function_md5_hello_world);
    RUN_TEST(test_function_md5_hello_another_string);
    UNITY_END();
}

void loop()
{
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}
