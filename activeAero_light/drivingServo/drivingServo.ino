/*
 * This code is used to find the min and max pulse lengths for the MKS servo
 * I have found at 60hz the servo min = .8ms and servo max = 2.05ms
 * or in terms of bit lengths min = 200 and max = 503
 * Also, the MKS servo unfortunately doesn't rotate a full 180 degrees.
 * Very roughly, it operates from 20 to 160 degrees for a full rotation of 140 degrees.
 * Note: orientation based on the MKS Logo arm. Holding the servo towards you, the logo
 * is on top with the 2 labeled arm on bottom. 
 */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//Create the pwm object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); //default address 0x40

//Global Variables
int freq = 60;
uint16_t lenBit_Min = 0;
uint16_t lenBit_Max = 0;


void setup() {
  Serial.begin(9600);
  Serial.println("Finding min and max pulse length for MKS Servo");

  //Initializing my pwm object
  pwm.begin();
  pwm.setPWMFreq(freq);
  yield();

  
  //Set Min and Max lengths
  //Input is in milliseconds, function converts to Bits
  lenBit_Min = pulseLength_to_bitLength(.8);
  lenBit_Max = pulseLength_to_bitLength(2.05);
  
}

void loop() {

  
  Serial.println("Moving Forward");
  //Drive servo forward
  for (uint16_t pLen = lenBit_Min; pLen < lenBit_Max; pLen++){
    //pwm.setPWM(port Number, start at 0, end at pLen)
    pwm.setPWM(0,0,pLen);
      
  }
  
  delay(500);

  Serial.println("Moving Backwards");
  //Drive servo backwards
  for (uint16_t pLen = lenBit_Max; pLen > lenBit_Min; pLen--){
    pwm.setPWM(0,0,pLen);
      
  }
  delay(500);
  
  

}

