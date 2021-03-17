#include <Arduino.h>
#include <unity.h>
#include <Ethernet.h>
#include <ArduinoHttpClient.h>
#include "config.h"

void tc__HttpClient__SimpleHttp(void)
{
    // Name of the server we want to connect to
    const char kHostname[] = "arduino.cc";
    // Path to download (this is the bit after the hostname in the URL
    // that you want to download
    const char kPath[] = "/";

    byte mac[] = ETHERNET_MAC;
    int conStat = Ethernet.begin(mac);
    TEST_ASSERT_EQUAL_INT(1, conStat);
    EthernetHardwareStatus status = Ethernet.hardwareStatus();
    TEST_ASSERT_EQUAL_INT(EthernetW5500, status);

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

void tc__HttpClient__FritzBox_connect(void)
{
    String pathNotExisting = "/doesNotExist.xml";
    String pathExisting = "/tr64desc.xml";

    byte mac[] = ETHERNET_MAC;
    int conStat = Ethernet.begin(mac);
    TEST_ASSERT_EQUAL_INT(1, conStat);

    EthernetClient c;
    HttpClient http(c, "fritz.box", 49000);
    int err = 0;
    int bodyLen = 0;

    err = http.get(pathNotExisting);
    TEST_ASSERT_EQUAL_INT(0, err);
    err = http.responseStatusCode();
    TEST_ASSERT_EQUAL_INT(404, err); // HTTP Code 404: not found
    bodyLen = http.contentLength();
    TEST_ASSERT_GREATER_THAN_INT32(0, bodyLen);
    http.stop();

    err = http.get(pathExisting);
    TEST_ASSERT_EQUAL_INT(0, err);
    err = http.responseStatusCode();
    TEST_ASSERT_EQUAL_INT(200, err); // HTTP Code 200: ok
    bodyLen = http.contentLength();
    TEST_ASSERT_GREATER_THAN_INT32(0, bodyLen);
    http.stop();
}
