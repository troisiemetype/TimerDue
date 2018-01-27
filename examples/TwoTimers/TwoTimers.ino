
#include "TimerDue.h"

TimerDue metro = TimerDue(0);
TimerDue second = TimerDue(1);

bool state = false;


void setup(){

	SerialUSB.begin(115200);

	delay(2000);
//	while(!SerialUSB);

//	SerialUSB.println("démarré");

	pinMode(13, OUTPUT);

	digitalWrite(13, LOW);

	metro.initMilliseconds(500);

	metro.attach(updateLed);

	metro.start();

	second.initMilliseconds(650);
	second.attach(updateLed);
	second.start();

}

void loop(){

}

void updateLed(){
	state = !state;
	digitalWrite(13, state);

}