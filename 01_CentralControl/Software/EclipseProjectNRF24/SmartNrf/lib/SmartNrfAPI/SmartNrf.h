#ifndef SMARTNRF_H
#define SMARTNRF_H
#include <RF24.h>;
#include <time.h>
#include <stdio.h>


enum Type {
	 ZENTRALE=0,FTS=1, ROBOTER=2, FLIESSBAND=3,UNDEFINED=4,ENDOFTYPES=5
};

enum Action {
	HELLO=0,ENDOFACTIONS=1
};

class SmartNrf {

// The various roles supported by this sketch
private:
	RF24 radio = RF24(7, 8);
	const byte addresses[3][6] = { "1Node", "2Node" };
	bool run;
	Type COMP;
	byte counter; // A single byte to keep track of the data being sent back and forth
	long STARTTIME;
	static unsigned const int PAYLOAD_SIZE = 32;
	//Indices for parsing
	static const byte TYPEINDEX=0;
	static const byte IDINDEX=1;
	static const byte ACTIONINDEX=2;

	static const char SmartNrf::TYPES [5];
	static const char SmartNrf::ACTIONS [1];
	byte registeredComponents [5];
	byte COMP_ID;

public:
	SmartNrf();
	void configurate(Type);
	void start();

	bool helloACK();
	void responseToHello(char,char,String);


	bool sendPayload(String);
	String recievedPayload();
	void handlePayload(String);
	bool runs();
	byte getTypeCount(Type);
	void registerType(Type);
	bool payloadSizeCheck(String);
	//Parsing methods
	static char typeChar(Type);
	static Type charType(char);
	static char actionChar(Action);
	static Action charAction(char);
};


#endif SMARTNRF_H
