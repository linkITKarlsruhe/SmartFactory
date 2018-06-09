#ifndef LINKITRF24_H
#define LINKITRF24_H

#include <PubSubClient.h>
#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>
#include <RF24Ethernet.h>
#include <RF24Mesh.h>

class LinkitRF24{

private:
  char *clientID;
public:
  void setup(MQTT_CALLBACK_SIGNATURE,char* );
  bool meshBegins();
  bool mqttConnected();
  bool connectMqtt();
  void publish(const char* , const char* );
  void subscribe(const char*);
  int clientState();
  bool clientLoop();
};

#endif
