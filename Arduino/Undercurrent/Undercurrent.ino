#include <MIDI.h>
#include "MidiSensor.h"

MidiSensor sensors[10]; 

void setup() { 
  
  pinMode(A0, INPUT); 
  pinMode(A1, INPUT); 
  
  MIDI.begin();   
  //Serial.begin(9600); 
  for(int i = 0; i<10; i++) { 
    // A6 is pin 60
    sensors[i].init(60+i, i+1, 0, 1024); 

  }
}


void loop() { 
  
  int minthreshold = 1024 - analogRead(A0); 
  int maxthreshold = 1024 - analogRead(A1); 
  for(int i = 0; i<10; i++) { 
    sensors[i].update(minthreshold, maxthreshold); 
    
    
  }
  //Serial.println(' ');

  delay(10); 

}



