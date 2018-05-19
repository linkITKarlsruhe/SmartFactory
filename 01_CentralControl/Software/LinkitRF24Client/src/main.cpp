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

#include "LinkitRF24Client.h"

LinkitRF24Client *linkit_client = new LinkitRF24Client();
//RF24 radio(7,8);
//RF24Network network(radio);
//RF24Mesh mesh(radio,network);
//RF24EthernetClass RF24Ethernet(radio,network,mesh);

//IPAddress ip(10,10,2,8);
//IPAddress gateway(10,10,2,2); //Specify the gateway in case different from the server
//IPAddress server(10,10,2,2);

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

//EthernetClient ethClient;
//PubSubClient client(ethClient);


void setup()
{
  Serial.begin(115200);

  //client.setServer(server, 1883);
  linkit_client->getPubSubClient().setCallback(callback);
  Serial.println("Before Start");

  //Ethernet.begin(ip);
  //Ethernet.set_gateway(gateway);
  //Serial.println("Before Mesh");
  //if (mesh.begin()) {
  //  Serial.println(" OK");
  //} else {
  //  Serial.println(" Failed");
  //}
  //clientID[13] = ip[3] + 48; //Convert last octet of IP to ascii & use in clientID
}

uint32_t mesh_timer = 0;

void loop()
{
  if(millis()-mesh_timer > 5000){ //Every 30 seconds, test mesh connectivity
    Serial.println("Loop");
    mesh_timer = millis();
    if( ! linkit_client->checkConnection() ){
        linkit_client->renewMeshAddress();
     }
  }
  if (!linkit_client->isConnected()) {
    linkit_client->reconnectClient();
  }
  linkit_client->startClientLoop();
}
/*
    © 2018 GitHub, Inc.
    Terms
    Privacy
    Security
    Status
    Help

    Contact GitHub
    API
    Training
    Shop
    Blog
    About

Press h to open a hovercard with more details.
*/
