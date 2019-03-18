#include <Arduino.h>
//#include <Adafruit_NeoPixel.h>
#include <FastLED.h>
#include <CapacitiveSensor.h>
//#include "LedPatterns.h"
#include "nExtSP.h"
#include "Controller.h"
#include "Board.h"
#include "Pentagramm.h"
#include "Sensors.h"
#include "RFIDTag.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

using namespace controller;
using namespace board;
//using namespace ledPatterns;
using namespace pentagramm;

bool ghostshown;

//RFID-READER
int mode = 3;
//nExtSP
NEXTSP nextsp; //communication between Esp's
bool isServer;//if true Esp is Master
//bool notReady;//to avoid blocking data
const int masterPIN = D0;//set to 5V to initialise Master
String sentData = "";//to avoid sending the same data again and again

//_______________BEGIN___ONEPURPLE____________________________________________________//
void onePurple(uint8_t wait, CRGB *strip, String key) {
  Serial.println("OnePurple");

  delay(wait);
  Serial.println("one Purple END");
}
//_______________END___ONEPURPLE____________________________________________________//

//_______________BEGIN___TWOPURPLE____________________________________________________//
void twoPurple(CRGB *strip) {
  for (int i = 0; i < 10; i++) {
    /* ol' Adafruit-Lib-Code
    strip->setPixelColor(4,strip->Color(255, 0, 0));
    strip->show();
    delay(1000);
    strip->setPixelColor(4, 0);
    strip->show();
    delay(1000);*/

    //TEST - with FastLED-Lib
    // Turn the LED on, then pause
    strip[i] = CRGB::Red; //(try Amethyst)
    FastLED.show();
    delay(500);
    // Now turn the LED off, then pause
    strip[i] = CRGB::Black;
    FastLED.show();
    delay(500);

  }
    Serial.println("one Purple END");
}
//_______________END___TWOPURPLE____________________________________________________//

//_______________BEGIN___GHOST___________________________________________________//
void displayGhost() {
  /*
  //G
  stripBoard_R0.setPixelColor(15, stripBoard_R0.Color(255, 0, 0));
  stripBoard_R0.setPixelColor(16, stripBoard_R0.Color(255, 0, 0));
  stripBoard_R0.show();
  delay(1000);
  stripBoard_R0.setPixelColor(15, stripBoard_R0.Color(0, 0, 0));
  stripBoard_R0.setPixelColor(16, stripBoard_R0.Color(0, 0, 0));
  //stripBoard_R0.show();
  //H
  stripBoard_R0.setPixelColor(13, stripBoard_R0.Color(255, 0, 0));
  stripBoard_R0.setPixelColor(14, stripBoard_R0.Color(255, 0, 0));
  stripBoard_R0.show();
  delay(1000);
  stripBoard_R0.setPixelColor(13, stripBoard_R0.Color(0, 0, 0));
  stripBoard_R0.setPixelColor(14, stripBoard_R0.Color(0, 0, 0));
  stripBoard_R0.show();
  //O
  stripBoard_R1.setPixelColor(25, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.setPixelColor(26, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.show();
  delay(1000);
  stripBoard_R1.setPixelColor(25, stripBoard_R1.Color(0, 0, 0));
  stripBoard_R1.setPixelColor(26, stripBoard_R1.Color(0, 0, 0));
  //stripBoard_R1.show();
  //S
  stripBoard_R1.setPixelColor(16, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.setPixelColor(17, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.show();
  delay(1000);
  stripBoard_R1.setPixelColor(16, stripBoard_R1.Color(0, 0, 0));
  stripBoard_R1.setPixelColor(17, stripBoard_R1.Color(0, 0, 0));
  //stripBoard_R1.show();
  //T
  stripBoard_R1.setPixelColor(14, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.setPixelColor(15, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.show();
  delay(1000);
  stripBoard_R1.setPixelColor(15, stripBoard_R1.Color(0, 0, 0));
  stripBoard_R1.show();
  */
}
//_______________END___GHOST________________________________________________//

//_______________BEGIN___CALLBACK___NEXTSP____________________________________________________//
void onCallback(byte* b,int length){
Serial.println("Callback called");
Serial.println((char)b[0]);
//String key = GetKey(b[0]);
//Serial.println("before onPurple call");
//onePurple(100, GetRow(key), key);

  delay(100);
  Serial.println("Callback finished");
}
//_______________END___CALLBACK___NEXTSP____________________________________________________//

//_________________________BEGIN___SETUP_________________________________________________//
void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println("Setup started");
  pinMode(masterPIN, INPUT); //server / client switch
  delay(100);
  isServer = digitalRead(masterPIN);
  delay(100);
  Serial.println(isServer);

  delay(100);
  //nextsp.begin(isServer,"OUIIIJAAA",&onCallback);
  delay(100);
  Serial.println("after esp begin");

    /*while(!nextsp.connected())
    {
        Serial.print(".");
        nextsp.update();
        delay(100);
    }

  //MASTER
  if(isServer){
    controller::setupController();
    Serial.println("controller setup ended");
    //pentagramm::setupCapacitiveSensor();
    setup_rfid();
    Serial.println("setup rfid success");
  }

  //CLIENT
  if(!isServer){
    board::setupBoard();
    Serial.println("board setup ended");
  }*/

  //board::setupBoard();
  /* OLD TEST
  pinMode(ledPIN_R0, OUTPUT);
  stripBoard_R0 = Adafruit_NeoPixel(LENGTH_BOARD_R0, ledPIN_R0, NEO_GRB + NEO_KHZ800);
  stripBoard_R0.begin();
  delay(100);
  ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
  delay(100);
  stripBoard_R0.show();
  */
  Serial.println("End Setup");
}
//_____________________END__SETUP_______________________________________________________//

//_____________________BEGIN__LOOP______________________________________________________//
   void loop()
   {
    Serial.println("Loop begin OUAHUUU");
    //onePurple(100, GetRow(key), key);

    Serial.println("HI");
    //ledPatterns::rainbow(50, &stripBoard_R0);
    delay(100);
    //displayGhost();
    twoPurple(stripBoard_R0);
    delay(50000);

      //TURN LED ON WITH CAPACITIVE SENSOR
      /*if (!isActive){
      //loop capacitiveSensor
      pentagramm::loopCapacitiveSensor();
      }*/

     /*if (!isServer) {
       Serial.println("Colors reset");
     }*/

     /*if(!isServer){
       if (!ghostshown){
       displayGhost();
       ghostshown = true;
       Serial.println("Ghost was shown");
       }
     }*/

/*______________WICHTIG________
     //String key = "DERP";//rfid().substring(1);
     if (isServer) {
       Serial.println(rfid().substring(1));
       String key = GetValue(rfid().substring(1));
       Serial.println(key);


     if (nextsp.connected() && !key.equals(sentData) && !key.equals("EMPTY")) {
         sentData = key;
         Serial.println(sentData);

            //ledPatterns::resetColor(LENGTH_CONTROLLER, &strip_Controller);
            Serial.println("000");

            /*if (GetValue(key) == "1") {
              //controller::activateMotor();
              Serial.println("444");
            }*/

            // AS vermutlich noch doof
          //  nextsp.send(key);
          //  delay(100);
          //  Serial.println("111");

  // }
  //}
   //delay(100);
   //update_rfid();
    //Serial.println("222");
    // geht laut elisa auch ohne
    //delay(100);
   //nextsp.update();
   //____END__WICHTIG*/

   Serial.println("END LOOP");
}
//____________________________END____LOOP_____________________________________________//
