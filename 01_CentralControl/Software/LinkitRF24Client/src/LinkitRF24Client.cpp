#include "LinkitRF24Client.h"

LinkitRF24Client::LinkitRF24Client(){

  radio = RF24(7,8);
  network = RF24Network(radio);
  mesh = RF24Mesh(radio,network);
  RF24Ethernet = RF24EthernetClass(radio,network,mesh);

  ip = IPAddress(10,10,2,8);
  gateway = IPAddress(10,10,2,2); //Specify the gateway in case different from the server
  server = IPAddress(10,10,2,2);

  EthernetClient ethClient;
  PubSubClient client(ethClient);

  client.setServer(server, 1883);
  //client.setCallback(callback);
  Serial.println("Before Start");

  Ethernet.begin(ip);
  Ethernet.set_gateway(gateway);
  Serial.println("Before Mesh");
  if (mesh.begin()) {
    Serial.println(" OK");
  } else {
    Serial.println(" Failed");
  }
  clientID[13] = ip[3] + 48; //Convert last octet of IP to ascii & use in clientID
}

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
