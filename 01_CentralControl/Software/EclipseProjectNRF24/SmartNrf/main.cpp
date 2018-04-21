//#include <Arduino.h>
//#include <RF24.h>
//#include "lib/SmartNrfAPI/SmartNrf.h"
//#include <string.h>
//
//SmartNrf smr;
//void setup() {
//	Serial.begin(115200);
//	smr = SmartNrf();
//	smr.setText("Willkommen");
//
//}
//
//int n=0;
//void loop() {
//Serial.print(smr.getText());
//Serial.println(n++);
//delay(500);
//}
/*
 Dec 2014 - TMRh20 - Updated
 Derived from examples by J. Coliz <maniacbug@ymail.com>
 */
/**
 * Example for efficient call-response using ack-payloads
 *
 * This example continues to make use of all the normal functionality of the radios including
 * the auto-ack and auto-retry features, but allows ack-payloads to be written optionlly as well.
 * This allows very fast call-response communication, with the responding radio never having to
 * switch out of Primary Receiver mode to send back a payload, but having the option to switch to
 * primary transmitter if wanting to initiate communication instead of respond to a commmunication.
 */

#include "lib/SmartNrfAPI/SmartNrf.h"
////#include <SPI.h>
////#include "RF24.h"
//
///****************** User Config ***************************/
///***      Set this radio as radio number 0 or 1         ***/
//bool radioNumber = 1;
//
///* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
//RF24 radio(7, 8);
///**********************************************************/
//// Topology
//byte addresses[][6] = { "1Node", "2Node" }; // Radio pipe addresses for the 2 nodes to communicate.
//
//// Role management: Set up role.  This sketch uses the same software for all the nodes
//// in this system.  Doing so greatly simplifies testing.
//typedef enum {
//	role_ping_out = 1, role_pong_back
//} role_e;                 // The various roles supported by this sketch
//const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back" }; // The debug-friendly names of those roles
//role_e role = role_pong_back;          // The role of the current running sketch
//
//byte counter = 1; // A single byte to keep track of the data being sent back and forth

SmartNrf sm = SmartNrf();

void setup() {

	Serial.begin(115200);
	Serial.println(F("RF24/examples/GettingStarted_CallResponse"));
	// Setup and configure radio
	sm.configurate(FTS);
}

void loop(void) {

	if(!sm.runs())sm.start();
}
