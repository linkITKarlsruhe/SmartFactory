#include "LinkitRF24Client.h"
#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>
#include <RF24Mesh.h>
#include <RF24Ethernet.h>
#include <PubSubClient.h>
// LinkitRF24Client::LinkitRF24Client(){
//
  // RF24 radio(7,8);
  // RF24Network network(radio);
  // RF24Mesh mesh(radio,network);
  // RF24EthernetClass RF24Ethernet(radio,network,mesh);
  //
  // IPAddress ip(10,10,2,8);
  // IPAddress gateway(10,10,2,2); //Specify the gateway in case different from the server
  // IPAddress server(10,10,2,2);
  //
  // EthernetClient ethClient;
  // PubSubClient client(ethClient);

//   client.setServer(server, 1883);
//   client.setCallback(callback);
//   Serial.println("Before Start");
//
//   Ethernet.begin(ip);
//   Ethernet.set_gateway(gateway);
//   Serial.println("Before Mesh");
//   if (mesh.begin()) {
//     Serial.println(" OK");
//   } else {
//     Serial.println(" Failed");
//   }
//   clientID[13] = ip[3] + 48; //Convert last octet of IP to ascii & use in clientID
// }

void LinkitRF24Client::reconnectClient() {
  // Loop until we're reconnected
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(clientID)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic","hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 5 seconds before retrying
      delay(2000);
    }
  }
}

PubSubClient LinkitRF24Client::getPubSubClient(){return client;}
bool LinkitRF24Client::isConnected(){return client.connected();}
void LinkitRF24Client::startClientLoop(){client.loop();}
bool LinkitRF24Client::checkConnection(){return mesh.checkConnection();}
void LinkitRF24Client::renewMeshAddress(){mesh.renewAddress();}
