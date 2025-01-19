/*

'VLP200 Sync' by Plank guitars and musical things by Shambien (Daniele Muscetta)
USed to solve a very specific shortcoming of the Valeton VLP200 pedal 
so that we can use the CTRL PEDAL input on the VLP200 to START the drums when receiving a MIDI start message and stop them when we receive a stop message

v.01 - initial beta


*/




#include <MIDI.h>

// for debug on Arduino UNO that has a LED on PIN13
// #define LED 13


MIDI_CREATE_DEFAULT_INSTANCE();

// pin to activate the relay
const int relayPin = A0;



void setup() {

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  // for debug on Arduino UNO that has a LED on PIN13
  // pinMode(LED, OUTPUT);

  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleStart(handleStart);
  MIDI.setHandleStop(handleStop);

}

void loop() {
  MIDI.read();
}


void handleStart() {
  // for debug on Arduino UNO that has a LED on PIN13
  // digitalWrite(LED, HIGH);
  
  sendShortPress();
}

void handleStop() {
  // for debug on Arduino UNO that has a LED on PIN13
  // digitalWrite(LED, LOW);

  sendShortPress();
}

void sendShortPress() {
  digitalWrite(relayPin, HIGH);
  delay(60);
  digitalWrite(relayPin, LOW);
}