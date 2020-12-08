/*
 * Project capstone_project
 * Description:  fill mold push onto conveyor & read RFID; reject molds with voids in fill
 * Author: Rodney Ham
 * Date:  03 December 2020 Thursday 2232
 */


#include <Adafruit_MQTT.h>
#include <credentials.h>
#include "Adafruit_MQTT/Adafruit_MQTT.h" 
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h" 
#include "Adafruit_MQTT/Adafruit_MQTT.h"  //Instructor Brian Rashap said although one file is a duplicate of the other, both are necessary; did not go into detail.
#include "Adafruit_SSD1306.h"
#include <Adafruit_BME280.h>
#include "Air_Quality_Sensor.h"
#include "HX711.h"


//stepper stuff
#include <Stepper.h>
const int steps=2048;   //2048 steps in one revolution.  This is a constant for this motor.  Change steps in void loop()
Stepper stepper(steps, D2, D4, D3, D5);    //IN1=D2, IN3=D4, IN2=D3, IN4=D5 order conneted to Argon

Adafruit_BME280 bme;

Servo myServo;      //create object myServo of class Servo

SYSTEM_MODE ( SEMI_AUTOMATIC );     //SEMI_AUTOMATIC to skip wifi internet connection
//SYSTEM_MODE ( AUTOMATIC );     //SEMI_AUTOMATIC to skip wifi internet connection


// #define OLED_RESET D4
// Adafruit_SSD1306 display(OLED_RESET);

// String DateTime , TimeOnly ;
// char currentDateTime [25] , currentTime [9];
/************************* Adafruit.io Setup *********************************/ 


/************ Global State (you don't need to change this!) ***   ***************/ 
TCPClient TheClient; 

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details. 
Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY);    //mqtt - object that defines the MQTT connection using the WiFi
                                                                                        //object, the MQTT server/port, and user name/password.




/****************************** Feeds ***************************************/ 
// Setup Feeds to publish or subscribe 
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname> 
//the var name after feeds must match dashboard block control name
//NOTE: FeedName, mqttObj, and value should be given descriptive ”names” similar to the naming convention for all variables and objects in the C++ code.
//Adafruit_MQTT_Subscribe mqttObj1 = Adafruit_MQTT_Subscribe (& mqtt , AIO_USERNAME "/ feeds /FeedNameA ");
//Adafruit_MQTT_Publish mqttObj2 = Adafruit_MQTT_Publish (& mqtt , AIO_USERNAME "/ feeds /FeedNameB ");
//refer to Class Slides "MQTT Publish and Subscribe"
//Adafruit_MQTT_Subscribe Receive_From_Cloud = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/waterManually"); //read breadboard & store in a var
Adafruit_MQTT_Publish temp_to_Cloud = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/room_temp_chrt");   //publish var to broker with this AIO user name recognized by mqtt
Adafruit_MQTT_Publish pressure_to_Cloud = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/bar_pressure");   //publish var to broker with this name
Adafruit_MQTT_Publish humidity_to_Cloud = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");   //publish var to broker with this name
Adafruit_MQTT_Publish AQ_to_Cloud = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/air_Quality");   //publish var to broker with this name
Adafruit_MQTT_Publish Dust_to_Cloud = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/dust_concentration");   //publish var to broker with this name

//WHEATSTONE_____WHEATSTONE_____/WHEATSTONE_____WHEATSTONE_____
// From the Command Palette install the HX711A library , that will give you HX711 .h
#define DOUT D6
#define CLK D8
HX711 myScale(DOUT,CLK);             // any two digital pins myScale(DOUT,CLK)

// FLASH WITH WEIGHT OFF WHEATSTONE THEN ADD THE WEIGHT
const int cal_factor=1933;          // changing value changes get_units units (lb , g, ton , etc .)
const int samples=10;              // number of data points averaged when using get_units or get_value
float weight, rawData, calibration;
int offset;


/************Declare Variables************/
//Dust_Sensor
unsigned long lastTime;
unsigned long duration;
unsigned long starttime;
unsigned long publish_time_ms = 12000;//sample 30s ;
unsigned long lowpulseoccupancy = 0;
float ratio=0, concentration=0;
int dustConsentrate;


unsigned long last;
float var_sent_to_dashboard,tempC,pressPA,humidRH;
int value,moisture,valueSlider,airQuality,status;

// Initialize objects from the lib
AirQualitySensor sensor(A5);


void setup() {
  Serial.begin(9600);
  // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // display.clearDisplay();   // clears the screen and buffer
  // delay(100);                             //wait for Serial Monitor to startup

  // sync_my_time(); // Ensure the Argon clock is up to date

  stepper.setSpeed(15);
  myServo.write(165);

  // text display texts
  // display.setTextSize(1);
  // display.setCursor(0,0);
  // display.setTextColor(WHITE);
  // display.display();
  // delay(2000);
  pinMode(A5,INPUT);      //Air quality sensor
  pinMode(A0,INPUT);      //Dust sensor
  pinMode(A1,INPUT);      //line_sensor
  pinMode(A2,OUTPUT);     //hopper servo motor

  myServo.attach(A2);     //attach the Servo object to a pin
  myServo.write(165);

  // Setup MQTT subscription for onoff feed.
  // mqtt.subscribe(&TempF);
  // mqtt.subscribe(&Receive_From_Cloud);    //Receive DATA from io.adafruit.com dashboard var "Receive_From_cloud"
 
  status=bme.begin(0x76);
    if(status==false){
    Serial.print("initialization failed");
    }

  //WHEATSTONE_____WHEATSTONE_____/WHEATSTONE_____WHEATSTONE_____
    myScale.set_scale();              // initialize loadcell by placing a known weight on it
    delay(5000);                      // let the loadcell settle
    myScale.tare();                   // set the tare weight (or zero )
    myScale.set_scale(cal_factor);   // adjust when calibrating scale to desired units
    //long zero_factor=scale.read_average(); //Get a baseline reading

}//THIS IS THE END OF void setup()


void loop() {
  //MQTT_connect();
  //OLED_display();
  Wheatstone_Br();
  door_hopper();   
  //Moisture();
  //round_table();
  //line_sensor();

  // if ((millis()-last)>120000) {           //connect - disconnect from dashboard
  //     Serial.printf("Pinging MQTT \n");
  //     if(! mqtt.ping()) {
  //       Serial.printf("Disconnecting \n");
  //       mqtt.disconnect();
  //     }
  //     last = millis();
  // }

// //     // this is our 'wait for incoming subscription packets' busy subloop
// //   // try to spend your time here
//   // Adafruit_MQTT_Subscribe *subscription;
//   // while ((subscription = mqtt.readSubscription(10000))) {       //Read dashboard & store into a var, wait 10 seconds
//   //   if (subscription == &Receive_From_Cloud) {                  // if the var and subscription from dashboard
//   //     value = atoi((char *)Receive_From_Cloud.lastread);        //read interger from dashboard & store in value i==int f==float
//   //                                                               //WHAT IS <.lastread>?
//   //     Serial.printf("value received from cloud %i \n", value);  //display block data from dashboard    
//   //   }
//   //   if(subscription==&email_From_Cloud){
//   //   Serial.printf("You Got Mail \n");
//   //   digitalWrite(D7,HIGH);
//   //   delay(10000);
//   //   digitalWrite(D7,LOW);
//   //   }
  //   if(millis()-lastTime>publish_time_ms) {    //publish to broker                 
  //   if(mqtt.Update()) {             //if mqtt ready to receive data then use publish   
  //   Serial.println("publishing to cloud");
  //     BME280();
  //     Air_Quality_Sensor();
  //     Dust_Sensor();
  //     temp_to_Cloud.publish(tempC); 
  //     pressure_to_Cloud.publish(pressPA);
  //     humidity_to_Cloud.publish(humidRH);
  //     AQ_to_Cloud.publish(airQuality);
  //     Dust_to_Cloud.publish(dustConsentrate);
  //     //moisture_to_Cloud.publish(moisture); 
  //   } 
  //   lastTime = millis();
  // }

}//THIS IS THE END OF void loop()
  


// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
  }
  Serial.println("MQTT Connected!");
}

// void sync_my_time()       // This function ensures the Argon clock is up to date
//   {
//   Time.zone(-7); // Set Time Zone to MST (UTC -7)
//   Particle.syncTime();
//   waitUntil(Particle.syncTimeDone);
//   }

// void OLED_display()
// {
//   DateTime=Time.timeStr (); // Get Current Time
//   TimeOnly=DateTime.substring (11,19); // Extract the Time from the DateTime String
//   // Convert String to char arrays - this is needed for formatted print
//   //DateTime.toCharArray ( currentDateTime ,25) ;
//   TimeOnly.toCharArray (currentTime,9);
//    // Print using formatted print
//   Serial.println("Rodney Ham");   //print on serial monitor
//   display.println("Rodney Ham");    //display on OLED moniter
//   //Serial.printf("Date and time is %s\n", currentDateTime );
//   Serial.printf("Time is %s\n", currentTime );
//   display.printf("Time is %s\n", currentTime );
//   display.display();
//   delay (2000) ; // only loop every 2 seconds
// }

void Wheatstone_Br() {
    // Using data from loadcell - be sure arrow on loadcell points toward the Earth
    weight=myScale.get_units(samples);    // return weight in units set by cal_factor ;
    //delay(4000);                           // add a short wait between readings
    Serial.printf("weight= %f \n",weight);
    // Other useful HX711 methods
    // rawData = myScale.get_value(samples) ;   // returns raw loadcell reading minus offset
    // offset = myScale.get_offset() ;            // returns the offset set by tare ();
    // calibration = myScale.get_scale() ;      // returns the cal_factor used by set_scale ();
    }

void door_hopper() {      
  if(weight<400) {
    myServo.write(180);         //if underweight open hopper door
    //Serial.printf("angle hopper door open %i \n",myServo.read());
  }
  else {
    if(myServo.read()==180){    //weight is proper and hopper door is still open
      myServo.write(165);       //close hopper door
      delay(500);               //slight delay for all product to fall into mold
      round_table();            //rotate round table to next position
      //Serial.printf("angle hopper door closed %i \n",myServo.read());
    }
  }
}

void BME280() {
  tempC=(bme.readTemperature()*9.0/5+32);
  if(tempC>75) {
    Serial.printf("WARNING: tempF=%0.2f \n",tempC);
  }
  pressPA=bme.readPressure()/(100.0*0.0002953);
  //if(pressPA<100) {
  //Serial.printf("pressPA=%0.2finHg \n",pressPA);
  //}
  humidRH=bme.readHumidity();
  //Serial.printf("humidRH=%0.2f \n",humidRH);
}

void Moisture(){
//   moisture=analogRead(A1);
//   Serial.printf("Moisture content is %i \n",moisture);
//   if(moisture>2500){
//     digitalWrite(A0,HIGH);    //make Argon pin A0 HIGH 
//     Serial.println("the motor is on") ;
//     delay(500);
//     digitalWrite(A0,LOW);      //if the dashboard box toggled a 0 make Argon pin A0 low
//   }
//   else{
//     digitalWrite(A0,LOW);
//   }
}

void Air_Quality_Sensor(){  
  sensor.slope();
  airQuality=sensor.getValue();
  if(airQuality>600){
  Serial.printf("WARNING: Matertial is contaminated %i \n",airQuality);
  delay(3000);
  }
}

void Dust_Sensor(){ 
    duration = pulseIn(A0,LOW);
    lowpulseoccupancy = lowpulseoccupancy+duration;
    if ((millis()-starttime) > publish_time_ms) {        //if the sample time == 30s
        ratio = lowpulseoccupancy/(publish_time_ms*10.0);  // Integer percentage 0=>100
        concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
        //Serial.printf("lowpulseoccupancy=%i, ratio=%f, concentration=%f \n",lowpulseoccupancy,ratio,concentration);
        lowpulseoccupancy = 0;
        dustConsentrate=concentration;
        if(dustConsentrate>5) {
        Serial.printf("WARNING: Dust concentration level %i \n",dustConsentrate );
        }
        starttime = millis();
    }
  }


void round_table(){
  // step one revolution  in one direction:
  // Serial.println("clockwise");
  // stepper.step(steps*2);
  // delay(2000);
  //
  // step one revolution in the other direction:
  //Serial.println("counterclockwise");
  stepper.step(-195);
  //delay(1000);
}

// void line_sensor(){
//   if(analogRead(A1)<1000) {
//     Serial.printf("White = %i \n",analogRead(A1));
//     delay(500);
//   }
//   else {
//     Serial.printf("Black = %i \n",analogRead(A1));
//     delay(500);
//   }
// }
  
