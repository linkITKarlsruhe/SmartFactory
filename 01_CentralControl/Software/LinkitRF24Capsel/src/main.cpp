/*
 *************************************************************************
   RF24Ethernet Arduino library by TMRh20 - 2014-2015
   Automated (mesh) wireless networking and TCP/IP communication stack for RF24 radio modules
   RF24 -> RF24Network -> UIP(TCP/IP) -> RF24Ethernet
                       -> RF24Mesh
        Documentation: http://tmrh20.github.io/RF24Ethernet/
 *************************************************************************
 *
 **** EXAMPLE REQUIRES: PubSub MQTT library: https://github.com/knolleary/pubsubclient ***
 *
 * Install using the Arduino library manager
 *
 *************************************************************************
  Basic MQTT example
 This sketch demonstrates the basic capabilities of the library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

*/

// #include "LinkitRF24Client.h"
#include <LinkitRF24.h>
// #include <PubSubClient.h>
// #include <SPI.h>
// #include <RF24.h>
// #include <RF24Network.h>
// #include <RF24Ethernet.h>
// #include <RF24Mesh.h>
#include <Time.h>
#include <time.h>
#include <string.h>
//#include <DateTimeStrings.h>
LinkitRF24 *linkit_client = new LinkitRF24();
// RF24 radio(7,8);
// RF24Network network(radio);
// RF24Mesh mesh(radio,network);
// RF24EthernetClass RF24Ethernet(radio,network,mesh);

// IPAddress gateway(10,10,2,2); //Specify the gateway in case different from the server
// IPAddress server(10,10,2,2);

char *clientID = {"arduinoClient"};

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// EthernetClient ethClient;
// PubSubClient client(ethClient);


void setup()
{
//   Serial.begin(115200);
//   client.setServer(server, 1883);
//   client.setCallback(callback);
//   Serial.println("Before Start");
//
//   Ethernet.begin(ip);
//   Ethernet.set_gateway(gateway);
//   Serial.println("Before Mesh");
//   bool beginsuc = false;
linkit_client->setup(callback,clientID);
while(!linkit_client->meshBegins()){
  delay(100);
     Serial.println(" Failed");
}
   Serial.println(" OK");
// while(!beginsuc){
//   if (mesh.begin(97)) {
//    Serial.println(" OK");
//    beginsuc = true;
//   } else {
//    Serial.println(" Failed");
//   }
//   delay(100);
//
// }
//   clientID[13] = ip[3] + 48; //Convert last octet of IP to ascii & use in clientID
}

uint32_t mesh_timer = 0;

void loop()
{
//   if(millis()-mesh_timer > 2000 && client.connected()){ //Every 30 seconds, test mesh connectivity
if(linkit_client->mqttConnected()){}
//     //time_t n = now();
//     // char buff[20];
//     // strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&n));

//     client.publish("smartfactory/fts","1214124214#12#123#333#111#444#111#444#999#2000#2000#2000#2000#2000#2000#2000#2000#0#124#1#0#75");
//     Serial.println("Send msg");
//     mesh_timer = millis();
//     if( ! mesh.checkConnection() ){
//         mesh.renewAddress();
//      }
//   }
//   if (!client.connected()) {
if(!linkit_client->mqttConnected())
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    //if(client.connect(clientID))
    if (linkit_client->connectMqtt()) {
      Serial.println("connected");
       // Once connected, publish an announcement...
//       client.publish("smartfactory/fts","hello world");
      linkit_client->publish("smartfactory/fts","hello world");
       // ... and resubscribe
//       client.subscribe("inTopic");
      linkit_client->subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      // Serial.print(client.state());
      Serial.print(linkit_client->clientState());
      Serial.println(" try in in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
//   }
// client.loop();
linkit_client->clientLoop();
}
