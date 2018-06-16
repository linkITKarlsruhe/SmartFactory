/*
 *************************************************************************
   RF24Ethernet Arduino library by TMRh20 - 2014-2015
   Automated (mesh) wireless networking and TCP/IP communication stack for RF24 radio modules
   RF24 . RF24Network . UIP(TCP/IP) . RF24Ethernet
                       . RF24Mesh
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

#include <LinkitRF24.h>
#include <Time.h>
#include <time.h>
#include <string.h>
//#include <DateTimeStrings.h>
LinkitRF24 linkit_client;

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

void setup()
{
Serial.begin(115200);
Serial.println("Before linkit setup");
linkit_client.setup(callback,clientID);
Serial.println("After linkit setup");

while(!linkit_client.meshBegins()){
  delay(100);
  Serial.println("Failed");
}
   Serial.println("OK, Arduino-Setup done");
}

uint32_t mesh_timer = 0;

void loop()
{
//   if(millis()-mesh_timer > 2000 && client.connected()){ //Every 30 seconds, test mesh connectivity
Serial.print("Arduino Loop");
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
if(!linkit_client.mqttConnected())
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    //if(client.connect(clientID))
    if (linkit_client.connectMqtt()) {
      Serial.println("connected");
       // Once connected, publish an announcement...
//       client.publish("smartfactory/fts","hello world");
      linkit_client.publish("smartfactory/fts","hello world");
       // ... and resubscribe
//       client.subscribe("inTopic");
      linkit_client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      // Serial.print(client.state());
      Serial.print(linkit_client.clientState());
      Serial.println(" try in in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
//   }
// client.loop();
linkit_client.clientLoop();
}
