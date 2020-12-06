/*
 * Project Servo_motor
 * Description:
 * Author:
 * Date:
 */
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