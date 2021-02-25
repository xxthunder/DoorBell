#include <Arduino.h>
#include "unity.h"
#include <Ethernet.h>
#include "ArduinoHttpClient.h"

void tc__HttpClient__SimpleHttp(void)
{
    // Name of the server we want to connect to
    const char kHostname[] = "arduino.cc";
    // Path to download (this is the bit after the hostname in the URL
    // that you want to download
    const char kPath[] = "/";

    byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
    int conStat = Ethernet.begin(mac);
    TEST_ASSERT_EQUAL_INT(1, conStat);

    EthernetClient c;
    HttpClient http(c, kHostname);
    int err = 0;

    err = http.get(kPath);
    TEST_ASSERT_EQUAL_INT(0, err);

    err = http.responseStatusCode();
    // TODO: how to use https?
    TEST_ASSERT_EQUAL_INT(301, err); // HTTP Code 301: permanently moved to https://www.arduino.cc/

    int bodyLen = http.contentLength();
    TEST_ASSERT_GREATER_THAN_INT32(0, bodyLen);
}
