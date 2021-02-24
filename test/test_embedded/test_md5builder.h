#include <Arduino.h>
#include "unity.h"
#include "MD5Builder.h"

#define MD5_STRING_LENGTH 32U

MD5Builder getMD5Builder(String text)
{
    MD5Builder md5Builder;
    md5Builder.begin();
    md5Builder.add(text);
    md5Builder.calculate();
    return md5Builder;
}

void tc__MD5builder__empty_string(void)
{
    MD5Builder md5Builder = getMD5Builder("");
    char md5[MD5_STRING_LENGTH];
    md5Builder.getChars(md5);
    TEST_ASSERT_EQUAL_STRING("d41d8cd98f00b204e9800998ecf8427e", md5);
    String md5String = md5Builder.toString();
    TEST_ASSERT_EQUAL_INT32(MD5_STRING_LENGTH, md5String.length());
    char __md5String[md5String.length() + 1];
    md5String.toCharArray(__md5String, md5String.length() + 1);
    TEST_ASSERT_EQUAL_STRING("d41d8cd98f00b204e9800998ecf8427e", __md5String);
}

void tc__MD5builder__hello_world(void)
{
    MD5Builder md5Builder = getMD5Builder("hello world");
    char md5[MD5_STRING_LENGTH];
    md5Builder.getChars(md5);
    TEST_ASSERT_EQUAL_STRING("5eb63bbbe01eeed093cb22bb8f5acdc3", md5);
    String md5String = md5Builder.toString();
    TEST_ASSERT_EQUAL_INT32(MD5_STRING_LENGTH, md5String.length());
    char __md5String[md5String.length() + 1];
    md5String.toCharArray(__md5String, md5String.length() + 1);
    TEST_ASSERT_EQUAL_STRING("5eb63bbbe01eeed093cb22bb8f5acdc3", __md5String);
}

void tc__MD5builder__another_string(void)
{
    MD5Builder md5Builder = getMD5Builder("Another string we would like to test.");
    char md5[MD5_STRING_LENGTH];
    md5Builder.getChars(md5);
    TEST_ASSERT_EQUAL_STRING("ee03459c0cd21889a9f383ba51cfa05e", md5);
    String md5String = md5Builder.toString();
    TEST_ASSERT_EQUAL_INT32(MD5_STRING_LENGTH, md5String.length());
    char __md5String[md5String.length() + 1];
    md5String.toCharArray(__md5String, md5String.length() + 1);
    TEST_ASSERT_EQUAL_STRING("ee03459c0cd21889a9f383ba51cfa05e", __md5String);
}
