
#ifndef LINKITRF24CLIENT_H
#define  LINKITRF24CLIENT_H

#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>
#include <RF24Mesh.h>
#include <RF24Ethernet.h>
#include <PubSubClient.h>

class LinkitRF24Client{

  RF24 radio;
  RF24Network network;
  RF24Mesh mesh;
  RF24EthernetClass RF24Ethernet;
  IPAddress ip;
  IPAddress gateway; //Specify the gateway in case different from the server
  IPAddress server;
  EthernetClient ethClient;
  PubSubClient client;
  char *clientID = {"arduinoClient"};
public:
  LinkitRF24Client();
  PubSubClient getPubSubClient(){return client;};
  bool isConnected(){return client.connected();};
  void startClientLoop(){client.loop();};
  void reconnectClient();
  bool checkConnection(){return mesh.checkConnection();};
  void renewMeshAddress(){mesh.renewAddress();};
};


#endif //LINKITRF24CLIENT_H
