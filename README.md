# PWMthruShiftRegister
Arduino Library to pump PWM signals through a shift register chain. Great for controlling LED chains

# When to use
A shift register or chain of shift registers can enable you to add digital IO to your Arduino beyond the limit of the Arduino's digital IO pins. This is possible because the Arduino can use a single pin to quickly "write out" the desired digital states of all the outputs of the shift register chain. This is great if you only need digital IO, but what if you wanted to, say, control 75 LEDs with PWM? You could still have a single Arduino pin "write out" the states, but these states would have to refresh rapidly, and you'd have to keep track of the duty for each state. PWMthruShiftRegsiter creates an "Analog Shift Regsiter" object which handles all the headache for you. All you have to do is connect up the Asr object to your shift register inputs and tell the Asr object at which level each output is on an analog scale that you can configure as needed.

# How it works
The Asr object receives analog levels (e.g. on a scale from 0 to 10) for each shift register output. It creates a counter for each output whose increment is proportional to the level for that output. By pulsing the output every time the counter overflows, Asr outputs a duty cycle which meets your specification and which is as uniform in time as possible.

# Applying PWMthruShiftRegsiter to your sketch
Check out the example sketch in this repository. Specifically, there is a three-way tradeoff between max global duty (e.g. max LED brightness), the number of levels (the analog resolution), and the noticeability of flicker. The comments in the example sketch explain how these tradeoff, and I recommend playing around with these values in order to see the tradeoff firsthand. After you understand the tradeoff, you'll be able to pick settings which are optimized for your application.
