/*
 * Project capstone_project
 * Description:  fill mold push onto conveyor & read RFID; reject molds with voids in fill
 * Author: Rodney Ham
 * Date:  30 November 2020 Monday
 */


// #include <Adafruit_MQTT.h>
// #include <credentials.h>
// #include "Adafruit_MQTT/Adafruit_MQTT.h" 
// #include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h" 
// #include "Adafruit_MQTT/Adafruit_MQTT.h"  //Instructor Brian Rashap said although one file is a duplicate of the other, both are necessary; did not go into detail.
// #include "Adafruit_SSD1306.h"
// #include <Adafruit_BME280.h>
//#include "Air_Quality_Sensor.h"

// Adafruit_BME280 bme;

Servo myServo;      //create object myServo of class Servo

SYSTEM_MODE ( SEMI_AUTOMATIC );     //SEMI_AUTOMATIC to skip wifi internet connection


// #define OLED_RESET D4
// Adafruit_SSD1306 display(OLED_RESET);

// String DateTime , TimeOnly ;
// char currentDateTime [25] , currentTime [9];
/************************* Adafruit.io Setup *********************************/ 


/************ Global State (you don't need to change this!) ***   ***************/ 
// TCPClient TheClient; 

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details. 
// Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY);    //referring to my adafruit account



// /****************************** Feeds ***************************************/ 
// // Setup Feeds to publish or subscribe 
// // Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname> 
// //the var name after feeds must match dashboard block control name
// Adafruit_MQTT_Subscribe Receive_From_Cloud = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/waterManually"); //read breadboard & store in a var

// Adafruit_MQTT_Publish temp_to_Cloud = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/room_temp_chrt");   //publish var to broker with this name
// Adafruit_MQTT_Publish moisture_to_Cloud = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/moisture_content");   //publish var to broker with this name
// Adafruit_MQTT_Publish pressure_to_Cloud = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/bar_pressure");   //publish var to broker with this name
// Adafruit_MQTT_Publish humidity_to_Cloud = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");   //publish var to broker with this name
// Adafruit_MQTT_Publish AQ_to_Cloud = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/air_Quality");   //publish var to broker with this name
// Adafruit_MQTT_Publish Dust_to_Cloud = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/dust_concentration");   //publish var to broker with this name



/************Declare Variables************/
// unsigned long last,lastTime,duration,starttime;
// unsigned long sampletime_ms = 30000;//sample 30s ;
// unsigned long lowpulseoccupancy = 0;
// float ratio = 0;
// float concentration = 0;
// int value,moisture,valueSlider,airQuality,dustConsentrate,status;
// float var_sent_to_dashboard,tempC,pressPA,humidRH;
//const int LED_7=A0;
// const int board_LED_on=A0;

// Initialize objects from the lib
// AirQualitySensor sensor(A2);


void setup() {
  Serial.begin(9600);
  // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // display.clearDisplay();   // clears the screen and buffer
  // delay(100);                             //wait for Serial Monitor to startup

  // sync_my_time(); // Ensure the Argon clock is up to date

  myServo.attach(A2);     //attach the Servo object to a pin

    // text display tests
  // display.setTextSize(1);
  // display.setCursor(0,0);
  // display.setTextColor(WHITE);
  // display.display();
  // delay(2000);
  // pinMode(A0,OUTPUT);     //for pump motor
  // pinMode(A1,INPUT);      //moisture sensor
  // pinMode(A2,INPUT);      //Air quality sensor
  // pinMode(A3,INPUT);      //Dust sensor
  // pinMode(A4,OUTPUT);       //Servo motor

  // Setup MQTT subscription for onoff feed.
  //mqtt.subscribe(&TempF);
  // mqtt.subscribe(&Receive_From_Cloud);    //Receive from io.adafruit.com dashboard
 
  // status=bme.begin(0x76);
  //   if(status==false){
  //   Serial.print("initialization failed");
  //   }
}         //THIS IS THE END OF void setup()


void loop() {
  // MQTT_connect();
  // OLED_display();
  door_hopper();
  // BME280();
  // Air_Quality_Sensor();
  // Dust_Sensor();
  // Conveyor();
  // Vibration();

  // if ((millis()-last)>120000) {           //connect - disconnect from dashboard
  //     Serial.printf("Pinging MQTT \n");
  //     if(! mqtt.ping()) {
  //       Serial.printf("Disconnecting \n");
  //       mqtt.disconnect();
  //     }
  //     last = millis();
  // }

//     // this is our 'wait for incoming subscription packets' busy subloop
//   // try to spend your time here
 
//   Adafruit_MQTT_Subscribe *subscription;
//   while ((subscription = mqtt.readSubscription(10000))) {       //Read dashboard & store into a var, wait 10 seconds
//     if (subscription == &Receive_From_Cloud) {                  // if the var and subscription from dashboard
//       value = atoi((char *)Receive_From_Cloud.lastread);        //read interger from dashboard & store in value i==int f==float
//                                                                 //WHAT IS <.lastread>?S
//       Serial.printf("value received from cloud %i \n", value);  //display block data from dashboard    

//     motor_hopper();
//     }

//     if(subscription==&email_From_Cloud)
//     {
//     Serial.printf("You Got Mail \n");
//     digitalWrite(D7,HIGH);
//     delay(10000);
//     digitalWrite(D7,LOW);
//     }
}       //THIS IS THE END OF void loop()
  

//   if(millis()-lastTime>5000)    //publish to broker
//   {                  
//     if(mqtt.Update())             //if mqtt ready to receive data then use publish
//     {                           
//       temp_to_Cloud.publish(tempC); 
//       moisture_to_Cloud.publish(moisture); 
//       pressure_to_Cloud.publish(pressPA);
//       humidity_to_Cloud.publish(humidRH);
//       AQ_to_Cloud.publish(airQuality);
//       Dust_to_Cloud.publish(dustConsentrate);
//     } 
//     lastTime = millis();
//   }
// }

// // Function to connect and reconnect as necessary to the MQTT server.
// // Should be called in the loop function and it will take care if connecting.
// void MQTT_connect() {
//   int8_t ret;
 
//   // Stop if already connected.
//   if (mqtt.connected()) {
//     return;
//   }
 
//   Serial.print("Connecting to MQTT... ");
 
//   while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
//        Serial.println(mqtt.connectErrorString(ret));
//        Serial.println("Retrying MQTT connection in 5 seconds...");
//        mqtt.disconnect();
//        delay(5000);  // wait 5 seconds
//   }
//   Serial.println("MQTT Connected!");
// }

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

void door_hopper() {
  myServo.write(180);
  Serial.println(myServo.read());
  delay(1000);
  myServo.write(160);
  delay(1000);
  Serial.println(myServo.read());
}

// void BME280()
// {
//   tempC=(bme.readTemperature()*9.0/5+32);
//   Serial.printf("tempF=%0.2f \n",tempC);
  
//   pressPA=bme.readPressure()/100.0*0.0002953;
//   Serial.printf("pressPA=%0.2finHg \n",pressPA);
  
//   humidRH=bme.readHumidity();
//   Serial.printf("humidRH=%0.2f \n",humidRH);

//   moisture=analogRead(A1);
//   Serial.printf("Moisture content is %i \n",moisture);
//   if(moisture>2500)
//   {
//     digitalWrite(A0,HIGH);    //make Argon pin A0 HIGH 
//     Serial.println("the motor is on") ;
//     delay(500);
//     digitalWrite(A0,LOW);      //if the dashboard box toggled a 0 make Argon pin A0 low
//   }
//   else
//   {
//     digitalWrite(A0,LOW);
//   }
  
// }

// void Air_Quality_Sensor(){  
//     sensor.slope();
//     airQuality=sensor.getValue();
//     Serial.println(airQuality);
//     delay(2000);
//   }

// void Dust_Sensor(){ 
//     duration = pulseIn(A3,LOW);
//     lowpulseoccupancy = lowpulseoccupancy+duration;
 
//     if ((millis()-starttime) > sampletime_ms)//if the sampel time == 30s
//     {
//         ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
//         concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
//         Serial.printf("lowpulseoccupancy=%i, ratio=%f, concentration=%f \n",lowpulseoccupancy,ratio,concentration);
//         lowpulseoccupancy = 0;
//         Serial.println("Dust is working");
//         dustConsentrate=concentration;
//         starttime = millis();
//     }
//   }

// void motor_hopper(){            //Need to 
//   if(value==1) {               //if the dashboard box toggled a 1 stored in value
//     myServo.write(180);        //open hopper door
//     delay(1000);
//     myServo.write(0);         //material weight is reached - close hopper door
//     delay(1000);
//     //myServo.read();
//     Serial.print("the motor is on") ;
//   }
//   else{
//      digitalWrite(A0,LOW);      //if the dashboard box toggled a 0 make Argon pin A0 low
//   }
// }

// void Conveyor(){

// }

// void Vibration(){

// }