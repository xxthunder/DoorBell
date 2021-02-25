#include <Arduino.h>
#include "unity.h"

#include "MD5.h"

char *md5_calc(char const *input)
{
    //generate the MD5 hash for our string
    unsigned char *hash = MD5::make_hash((char *)input);
    //generate the digest (hex encoding) of our hash
    char *md5str = MD5::make_digest(hash, 16);
    free(hash);
    return (md5str);
}

void tc__MD5__empty_string(void)
{
    char *md5str = md5_calc("");
    TEST_ASSERT_EQUAL_STRING("d41d8cd98f00b204e9800998ecf8427e", md5str);
    free(md5str);
}

void tc__MD5__hello_world(void)
{
    char *md5str = md5_calc("hello world");
    TEST_ASSERT_EQUAL_STRING("5eb63bbbe01eeed093cb22bb8f5acdc3", md5str);
    free(md5str);
}

void tc__MD5__hello_another_string(void)
{
    char *md5str = md5_calc("Another string we would like to test.");
    TEST_ASSERT_EQUAL_STRING("ee03459c0cd21889a9f383ba51cfa05e", md5str);
    free(md5str);
}
