
#include "Arduino.h"
#include <Midi.h>

class MidiSensor {

public : 

  int inputPin; 
  int outputChannel; 
  int minThreshold; 
  int maxThreshold; 
  int lastLevel;
  int midiChannel; 

  float currentVolume; 
  float riseSmoothSpeed;
  float fallSmoothSpeed;

  MidiSensor() { 
    currentVolume = 0; 
    riseSmoothSpeed = 0.1;  
    fallSmoothSpeed = 1;    
    lastLevel = 0;
    minThreshold = 0; 
    maxThreshold = 1024; 
  }

  void init(int inputpin, int midichannel, int minthreshold, int maxthreshold) { 

    inputPin = inputpin; 
    pinMode(inputPin, INPUT); 
    midiChannel = midichannel; 
    minThreshold = minthreshold; 
    maxThreshold = maxthreshold; 
    MIDI.sendControlChange(7, currentVolume, midiChannel); 

  }

  void update(int minthreshold, int maxthreshold) { 
    
    minThreshold = minthreshold; 
    maxThreshold = maxthreshold; 
    
    // get new volume dependent on the analogue sensor reading
    float newVolume = mapFloat(analogRead(inputPin), minThreshold, maxThreshold, 0, 127);

    // smoothing algorithm to make the current volume smooth to the new target
    // note different smoothing for rising and falling
    if(currentVolume<newVolume) { 
      currentVolume += (newVolume - currentVolume) * riseSmoothSpeed; 
    } 
    else { 
      currentVolume -= fallSmoothSpeed; 
    }

    //currentVolume = map(analogRead(inputPin), minThreshold, maxThreshold, 0, 127);
    // only send a midi message if 
    if(abs(currentVolume-lastLevel) > 1) { 

      // volume change is code 7
      MIDI.sendControlChange(7, currentVolume, midiChannel); 
      lastLevel = currentVolume;  


    }

    //Serial.print(newVolume); 
    //Serial.print('\t'); 



  }

  float mapFloat(float in, float min1, float max1, float min2, float max2) {
    if(in<min1) return min2; 
    if(in>max1) return max2; 
    return ((in-min1)/(max1-min1) * (max2-min2)) + min2; 
  }









}; 





