/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/yendo/Documents/IoT/IoT-2/capstone_project/experiment_folder/src/experiment_folder.ino"
/*
 * Project experiment_folder
 * Description:
 * Author:
 * Date:
 */

void setup();
void loop();
void line_sensor();
void round_table();
#line 8 "c:/Users/yendo/Documents/IoT/IoT-2/capstone_project/experiment_folder/src/experiment_folder.ino"
SYSTEM_MODE ( SEMI_AUTOMATIC );     //SEMI_AUTOMATIC to skip wifi internet connection
//SYSTEM_MODE ( AUTOMATIC );     //SEMI_AUTOMATIC to skip wifi internet connection


// setup() runs once, when the device is first turned on.
void setup() {
Serial.begin(9600); 
pinMode(A1,INPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    //line_sensor();
    round_table();
}

void line_sensor(){
  if(analogRead(A1)<1000) {
    Serial.printf("White = %i \n",analogRead(A1));
    delay(500);
  }
  else {
    Serial.printf("Black = %i \n",analogRead(A1));
    delay(500);
  }
}

void round_table(){
  Serial.println("counterclockwise");
  stepper.step(-195);
  delay(1000);

}
