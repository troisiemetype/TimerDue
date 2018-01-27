
#include "TimerDue.h"

TimerDue metro = TimerDue(0);

bool state = false;


void setup(){

	SerialUSB.begin(115200);

	delay(2000);
//	while(!SerialUSB);

	SerialUSB.println("démarré");

	pinMode(13, OUTPUT);

	digitalWrite(13, LOW);

	metro.initFrequency(2);

	metro.attach(updateLed);

	metro.start();

}

void loop(){

}

void updateLed(){
	if(state){
		digitalWrite(13, LOW);
		state = false;
	} else {
		digitalWrite(13, HIGH);
		state = true;
	}

}