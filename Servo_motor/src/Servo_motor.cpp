/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/yendo/Documents/IoT/IoT-2/capstone_project/Servo_motor/src/Servo_motor.ino"
/*
 * Project Servo_motor
 * Description:
 * Author:
 * Date:
 */
void setup();
void loop();
#line 7 "c:/Users/yendo/Documents/IoT/IoT-2/capstone_project/Servo_motor/src/Servo_motor.ino"
SYSTEM_MODE ( SEMI_AUTOMATIC );     //SEMI_AUTOMATIC to skip wifi internet connection

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
pinMode(D2,OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
digitalWrite(D2,HIGH);

Serial.print("kdjoief");
}