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
  // RF24 radio;
  // RF24Network network;
  // RF24Mesh mesh;
  // RF24EthernetClass RF24Ethernet;
  char *clientID;
public:
  // LinkitRF24(): radio(7,8),network(radio),mesh(radio,network),RF24Ethernet(radio,network,mesh){}
  void setup(MQTT_CALLBACK_SIGNATURE,char* );
  bool meshBegins();
  bool mqttConnected();
  bool connectMqtt();
  void publish(const char* , const char* );
  void subscribe(const char*);
  int clientState();
  bool clientLoop();
};

// class PubSubClient;
// class SPI;
// class RF24;
// class RF24Network;
// class RF24Ethernet;
//  class RF24Mesh;
#endif
