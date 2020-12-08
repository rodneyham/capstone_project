/*
 * Project experiment_folder
 * Description:
 * Author:
 * Date:
 */

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
