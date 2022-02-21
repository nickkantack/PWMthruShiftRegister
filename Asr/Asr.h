/*
  Asr.h - Library for passing different PWM
  driving signals through a chain of shift
  registers.
  
  Nick Kantack 1-9-2019
  Released into the public domain.
*/




#ifndef Asr_h
#define Asr_h

#include "Arduino.h"

class Asr{
  public:
		Asr(int LEDs_in, int resolution_in, int dataPin_in, int clockPin_in, int latchPin_in, int outputEnable_in);
		void watchShift();
		void shift();
		void commit(int state);
		int LEDs;
		int resolution;
		int *Vals;
		int *Count;
		int *State;
		long timeToShift;
		long dwellTime;
		int latchPin;
		int clockPin;
		int dataPin;
		int outputEnable;
		bool clockState;
};

#endif
