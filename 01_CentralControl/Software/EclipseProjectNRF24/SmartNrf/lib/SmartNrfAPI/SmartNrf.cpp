/*
 * SmartNrf.cpp
 *
 *  Created on: 19.01.2018
 *      Author: mario
 */
#include "SmartNrf.h"

static const char SmartNrf::TYPES[5] = { 'F', 'R', 'Z', 'B', 'U' };
static const char SmartNrf::ACTIONS[1] = { 'H' };

SmartNrf::SmartNrf() {
	/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
	radio = RF24(7, 8);
	run = false;
	COMP = UNDEFINED;
	counter = 1;
	COMP_ID =0;
	STARTTIME = micros();
	counter = 0;

}

void SmartNrf::configurate(Type type) {
	COMP = type;
	run = false;
	radio.begin();
	radio.enableAckPayload();                     // Allow optional ack payloads
	radio.enableDynamicPayloads();          // Ack payloads are dynamic payloads

	if (COMP == ZENTRALE) {
		radio.openWritingPipe(addresses[1]); // Both radios listen on the same pipes by default, but opposite addresses
		radio.openReadingPipe(1, addresses[0]); // Open a reading pipe on address 0, pipe 1
	} else {
		radio.openWritingPipe(addresses[0]);
		radio.openReadingPipe(1, addresses[1]);
	}
	radio.startListening();                       // Start listening

	radio.writeAckPayload(1, &counter, 1); // Pre-load an ack-paylod into the FIFO buffer for pipe 1

}
void SmartNrf::start() {
	run = true;

	if (COMP == ZENTRALE) {
		Serial.println("Start Centrale at ");
		radio.startListening();
		while (true) {
			handlePayload(recievedPayload());
		}
		Serial.println("Centrale started listening");
	} else {
		//sending 'hello' till Centrale response successful
		sendPayload("sen");
		Serial.println("Start Component  at ");
		while (!helloACK()) {
			delay(250);
		}

		Serial.println("COMP start handle recieved");
		while (true) {
			//radio.startListening();
			handlePayload(recievedPayload());
		}

	}
}

bool SmartNrf::runs() {
	return run;
}

bool SmartNrf::sendPayload(String payload) {
	bool ack = false;
	radio.stopListening();     // First, stop listening so we can talk.
	Serial.print(F("Now sending "));
	Serial.println(&payload[0]);

	if (radio.write(&payload[0], sizeof(payload))) {
		ack = radio.available();
	} else {
		// If no ack response, sending failed
		Serial.println(F("Sending failed."));
	}
	radio.startListening();
	return ack;
}

String SmartNrf::recievedPayload() {
	/****************** Pong Back Role ***************************/
	byte pipeNo;
	char gotByte[PAYLOAD_SIZE] = "0"; // Declare variables for the pipe and the byte received
	while (radio.available(&pipeNo)) {    // Read all available payloads
		radio.read(&gotByte[0], PAYLOAD_SIZE);
		// Since this is a call-response. Respond directly with an ack payload.
		Serial.print(F("Loaded next response"));
		Serial.println(gotByte);
	}
	return String(gotByte);
}
void SmartNrf::handlePayload(String payload) {

	if(payloadSizeCheck(payload)){
		char ty = payload[TYPEINDEX];
		char id = payload[IDINDEX];
		char action = payload[ACTIONINDEX];
		payload = payload.substring(ACTIONINDEX);
		//how big is the actual payload?
		//Validate
		if(ty!=COMP){
			Serial.println("Wrong component!");
			return;
		}

		//if "Zentrale" recieved a hello
		switch(action){
		case HELLO:
			responseToHello(ty,id,payload);
			break;
		default:break;
		}


	}else{
		Serial.println("Wrong payload size!");
	}
}

byte SmartNrf::getTypeCount(Type t) {
	return registeredComponents[t];
}
static Type SmartNrf::charType(char c){
	for(byte i =0; i< ENDOFTYPES;++i){
		if(c== typeChar((Type)i))return (Type)i;
	}
}
static char SmartNrf::typeChar(Type t) {
	return SmartNrf::TYPES[t];
}
static char SmartNrf::actionChar(Action a) {
	return SmartNrf::ACTIONS[a];
}
static Action SmartNrf::charAction(char c){
	for(int i =0; i< ENDOFACTIONS;++i){
		if(c== actionChar((Action)i))return (Action)i;
	}
}

bool SmartNrf::helloACK() {
	String payload = "";
	payload.concat(typeChar(COMP));
	payload.concat(String(COMP_ID, 10)); //edfault component id
	payload.concat(actionChar(HELLO));
	//conver long to char*
	payload.concat(String(STARTTIME, 10));
	byte gotByte = 0;
	if (!sendPayload(payload)) { // If nothing in the buffer, we got an ack but it is blank
		return false;
	} else {
		while (radio.available()) { // If an ack with payload was received
			radio.read(&gotByte, 1); // Read it, and display the response time
			Serial.print(F("Got response "));
			Serial.print(gotByte);
			radio.startListening();
		}
		return true;
	}
	handlePayload(recievedPayload());

}

void SmartNrf::responseToHello(char tychar, char idchar, String payload){
	//convert id to byte
	byte id = -1;
	if(isdigit(id)){
		id = idchar - '0';
	}else{
		//error
	}
	//get Type by char
	Type ty = charType(tychar);
	//get Type count and register new one
	byte idbyte = getTypeCount(ty);
	//get count of registered Types and increment
	registerType(ty);
	//create helloACK-Payload
	String ackpay = "";
	ackpay.concat(typeChar(COMP));
	ackpay.concat((char) (COMP_ID+'0'));
	ackpay.concat(actionChar(HELLO));
	ackpay.concat(payload);
	ackpay.concat((char)(idbyte + '0'));
	//send package
	while(!sendPayload(ackpay)){};
	recievedPayload()
}
void SmartNrf::registerType(Type ty){
	registeredComponents[ty]++;
}
bool SmartNrf::payloadSizeCheck(String s){

	return s.length()==32;
}
