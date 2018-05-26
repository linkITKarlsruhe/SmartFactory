
#ifndef LINKITRF24CLIENT_H
#define  LINKITRF24CLIENT_H

#include <PubSubClient.h>
#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>
#include <RF24Ethernet.h>
#include <RF24Mesh.h>

class RF24Ethernet;

class LinkitRF24Client{

private:
  RF24 radio;// = RF24(7,8);
  RF24Network network;// = RF24Network(radio);
  RF24Mesh mesh = RF24Mesh(radio,network);
  RF24EthernetClass rF24Ethernet = RF24EthernetClass(radio,network,mesh);
  //
  // IPAddress ip = IPAddress(10,10,2,8);
  // IPAddress gateway= IPAddress(10,10,2,2); //Specify the gateway in case different from the server
  // IPAddress server= IPAddress(10,10,2,2);

  EthernetClient ethClient;
  PubSubClient client = PubSubClient(ethClient);
  char *clientID = {"arduinoClient"};

public:
  LinkitRF24Client():radio(RF24(7,8)),network(RF24Network(radio)),mesh(RF24Mesh(radio,network)),rF24Ethernet(RF24EthernetClass(radio,network,mesh)),client(PubSubClient(ethClient)){};

  PubSubClient getPubSubClient();
  bool isConnected();
  void startClientLoop();
  void reconnectClient();
  bool checkConnection();
  void renewMeshAddress();
};


#endif //LINKITRF24CLIENT_H
