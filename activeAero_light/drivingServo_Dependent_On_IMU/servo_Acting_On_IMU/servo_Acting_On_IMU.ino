/*
 * This code demonstrates 'actuating' the servo when the IMU 
 * passes a certain angular frequency threshold. 
 */


#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

//Create the imu object
Adafruit_BNO055 bno = Adafruit_BNO055(55); //default address 0x55

//Create the pwm object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); //default address 0x40

//Global Variables
int freq = 60;
uint16_t lenBit_Min = 200;
uint16_t lenBit_Max = 503;
float wX = 0;
float wY = 0;
float wZ = 0;
uint16_t angle = 20;
uint16_t pLen = lenBit_Min;

void setup() {
  Serial.begin(9600);
  Serial.println("Switching between 20 and 160 degrees when IMU passes Threshold");




  /********************************************************************************
   * 
   * Setting up the IMU
   * 
   */
   //******************************************************************************

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);

  /* Display some basic information on this sensor */
  displaySensorDetails();

  /* Optional: Display current status */
  displaySensorStatus();

  bno.setExtCrystalUse(true);






  /********************************************************************************
   * 
   * Setting up the PWM
   * 
   */
  //*******************************************************************************

  //Initializing my pwm object
  pwm.begin();
  pwm.setPWMFreq(freq);
  yield();


  
}

void loop() {

  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);

  wX = gyro.x();
  wY = gyro.y();
  wZ = gyro.z();
  Serial.print(wX);
  Serial.print(",");
  Serial.print(wY);
  Serial.print(",");
  Serial.println(wZ);

  if( abs(wX) > .1 || abs(wY) > .1 || abs(wZ) > .1 ){
    Serial.println("Passed Threshold!");

    if(angle == 20){
      angle = 160;
    }else {
      angle = 20;
    }

    
  }


  pLen = map(angle, 20, 160, lenBit_Min, lenBit_Max);
  pwm.setPWM(0,0,pLen);
  

}



