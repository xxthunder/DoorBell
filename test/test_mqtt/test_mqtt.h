#include <Arduino.h>
#include <unity.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include "config.h"

void subscribeReceive(char *topic, byte *payload, unsigned int length)
{
}

void tc__mqttclient(void)
{
    byte mac[] = ETHERNET_MAC;
    int conStat = Ethernet.begin(mac);
    TEST_ASSERT_EQUAL_INT(1, conStat);
    EthernetHardwareStatus status = Ethernet.hardwareStatus();
    TEST_ASSERT_EQUAL_INT(EthernetW5500, status);

    const char *broker = MQTT_BROKER;
    EthernetClient ethClient;
    PubSubClient mqttClient(broker, 1883, ethClient);
    mqttClient.setBufferSize(255);
    TEST_ASSERT_EQUAL(true, mqttClient.connect(MQTT_ID, MQTT_USER, MQTT_PASSWD));
    TEST_ASSERT_EQUAL(true, mqttClient.publish(MQTT_ID, "Hello World"));

    /*
    - Debug command on openhab:
    openhabian@openhabian:~ $ mosquitto_sub -d -t "#" -u *** -P "***"
    Client mosqsub|8395-openhabian sending CONNECT
    Client mosqsub|8395-openhabian received CONNACK (0)
    Client mosqsub|8395-openhabian sending SUBSCRIBE (Mid: 1, Topic: DoorBell, QoS: 0)
    Client mosqsub|8395-openhabian received SUBACK
    Subscribed (mid: 1): 0
    Client mosqsub|8395-openhabian received PUBLISH (d0, q0, r0, m0, 'DoorBell', ... (11 bytes))
    Hello World
    */
}
