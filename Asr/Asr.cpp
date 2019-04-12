/*
  Asr.h - Library for passing different PWM
  driving signals through a chain of shift
  registers.
  
  Nick Kantack 1-9-2019
  Released into the public domain.
*/



#include "Arduino.h"
#include "Asr.h"

Asr::Asr(int LEDs_in, int resolution_in, int dataPin_in, int clockPin_in, int latchPin_in, int outputEnable_in){

	latchPin = latchPin_in;
	LEDs = LEDs_in;
	resolution = resolution_in;
	dataPin = dataPin_in;
	clockPin = clockPin_in;
	latchPin = latchPin_in;
	outputEnable = outputEnable_in;

	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(outputEnable, OUTPUT);

	Vals = new int[LEDs];
	Count = new int[LEDs];
	State = new int[LEDs];

	for (int i = 0; i < LEDs; i++){
		Vals[i] = 0;
	}


	for (int i = 0; i < LEDs; i++){
		Vals[i] = 0;
		Count[i] = 0;
		State[i] = 0;
	}

	timeToShift = micros();
	dwellTime = 500; // microseconds

}

void Asr::watchShift(){

	if (micros() > timeToShift){
		shift();
		timeToShift = micros() + dwellTime;
  	}

}

void Asr::shift(){
	
	/*
	shift is an algorithm to automatically distribute the requested duty as evenly as possible through the (resolution) number
	of subdivisions (each (dwellTime) microseconds long) of the complete update period ((dwellTime)*(resolution)) microseconds
	in length. It accomplishes this by maintaining a counter for each output whose incremental step size is proportional to
	the desired duty. Each overflow of the counter marks the time for the next pulse.
	*/
	
	digitalWrite(outputEnable, HIGH); // Setting this HIGH turns off outputs - good so that data is not seen shifting through register
  	for (int i = LEDs - 1; i >= 0; i--){
		// First set states LOW - this is a challenge conditions; they will soon be set HIGH if they are supposed to be on.
		State[i] = LOW;
		
		Count[i] += Vals[i]; // Increment the counter by the value
		if (Count[i] >= resolution){ // If the counter plus the value rolled over, change the state of the LED. This distributes the duty as evenly as possible
			Count[i] -= resolution;
			State[i] = HIGH;
		}
		// Write states to register
		commit(State[i]);
  	}
	digitalWrite(outputEnable, LOW); // Setting this LOW turns on all the outputs simultaneously

}

void Asr::commit(int state){

	digitalWrite(dataPin, state);
	digitalWrite(clockPin, HIGH);
	digitalWrite(latchPin, LOW);
	digitalWrite(clockPin, LOW);
	digitalWrite(latchPin, HIGH);

}
