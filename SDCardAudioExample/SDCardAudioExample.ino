/* 
  This sketch uses a LightBlue Bean to play an audio file from an SD card. 
  
  In the example, a LightBlue Bean is put in an elevator and plays an alarm
  as soon as the elevator moves.
    
  This example code is in the public domain.
*/

#include <SD.h>
#define SD_ChipSelectPin 2
#include <TMRpcm.h>

TMRpcm tmrpcm;

// These thresholds are used to check if the elevators is moving up or down
// They may have to be adjusted depending on how fast your elevator moves
int upperThreshold = 290;
int lowerThreshold = 220;

void setup(){
  // The pin that is connected to the speaker
  tmrpcm.speakerPin = 1;
  Serial.begin();
  
  // Check if the card is present and can be initialized
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }
}

void loop(){
  // Get the current acceleration with range of ±2g, and a conversion of 3.91×10-3 g/unit or 0.03834(m/s^2)/units. 
  AccelerationReading acceleration = Bean.getAcceleration();
  
  Serial.println(acceleration.zAxis);
  // Check if the elevator is moving
  if(acceleration.zAxis > upperThreshold || acceleration.zAxis < lowerThreshold){
     //Wait for three seconds
    delay(3000);
    // Play the audio file

    tmrpcm.play("alarm.wav");
    // Wait for 15 seconds before we check the accelerometer again
    delay(15000);
  }
  Bean.sleep(100);
}

