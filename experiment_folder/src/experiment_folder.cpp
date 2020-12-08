/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "c:/Users/yendo/Documents/IoT/IoT-2/capstone_project/experiment_folder/src/experiment_folder.ino"
/* 
 *  Project:  L05_02_neoPixel
 *  Description:  lighting up pixels
 *  Author:  Rodney Ham
 *  date:  13 Oct 2020
 */


#include "Particle.h"
#include <neopixel.h>
#include<colors.h>

void setup();
void loop();
#line 13 "c:/Users/yendo/Documents/IoT/IoT-2/capstone_project/experiment_folder/src/experiment_folder.ino"
SYSTEM_MODE(SEMI_AUTOMATIC);     //SEMI_AUTOMATIC to skip wifi internet connection
//SYSTEM_MODE ( AUTOMATIC );     //SEMI_AUTOMATIC to skip wifi internet connection

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_COUNT 13
#define PIXEL_PIN A3
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel pixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
int _delay=125;

void setup(){
  pixel.begin();  //initalize pixel allows you to talk to them
  pixel.setBrightness(63);  //how bright to make the pixels
  pixel.show();   //initalize all off
 // _delay=125;
}

void loop(){
  pixel.clear();  // clear the pixels
  pixel.show(); 

  //Light up the 4 pixels and the ring using a FOR-loop
  for(int i=4;i<8;i++){
    pixel.setPixelColor(i,red);
    pixel.show();
    delay(_delay);
  }

//    //single pixel going up
//  for(i=0;i<num_pix;i++){
//     pixel.setPixelColor(i,red_color,green_color,blue_color);  
//     pixel.show();
//     delay(_delay);
//     pixel.clear();
//   }
//     //Single pixel coming back
//   pixel.clear();
//  pixel.show();   
//     for(i=num_pix;i>0;i--){
//     pixel.setPixelColor(i,red_color,green_color,blue_color);  
//     pixel.show();
//     delay(_delay);
//     pixel.clear();
//     }

//     //rainbow going up
//     pixel.clear();
//    for(x=0;x<num_pix;x=x+7){
//       for(i=0;i<7;i++){
//          pix=x+i;
//          color=rainbow[i];
//          pixel.setPixelColor(pix,color);
//          pixel.show();
//          delay(_delay);
//       }
//    }
//    //rainbow blacking out on way down
//    for(x=num_pix;x>=0;x--){
//     pixel.setPixelColor(x,black);  
//     pixel.show();
//     delay(_delay);
//    }
//    delay(1000);

//     //send a pair of Maize and Blue light down the strip
//   for(i=0;i<num_pix;i=i+2){
//     pixel.setPixelColor(i,blue); 
//     pixel.setPixelColor(i+1,maize);
//     pixel.show();
//     delay(_delay);
//     pixel.clear();
//   }

//     //lLight up 6 segments sof different colors using the fill() method
//   for(i=0;i<num_pix;i=i+6){
//     color=rainbow[i/6];
//     pixel.fill(color,i,6);
//     pixel.show();
//     delay(_delay);

    
//   }
}
    
    
