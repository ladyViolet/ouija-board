#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <CapacitiveSensor.h>
#include "LedPatterns.h"
#include "nExtSP.h"
#include "Controller.h"
#include "Board.h"
#include "Pentagramm.h"
#include "Sensors.h"
#include "RFIDTag.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

//LED
 // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
// End of trinket special code

using namespace controller;
using namespace board;
using namespace ledPatterns;
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
void onePurple(int wait, Adafruit_NeoPixel *strip, String key) {
  Serial.println("OnePurple");
  //Serial.println(strip->numPixels());
  for(int i = 0; i < strip->numPixels(); i++) {
    if(i >= GetID(key) && i < GetLength(key)+GetID(key)) {
      Serial.println(GetID(key));
      Serial.println(GetLength(key)+GetID(key));
      strip->setPixelColor(i, strip->Color(0, 0, 255));
      //strip->setPixelColor(i, strip->Color(148, 0, 211));
    }else{
      strip->setPixelColor(i, strip->Color(0, 0, 0));
    }
  }
  strip->show();
  delay(wait);
  Serial.println("one Purple END");
}
//_______________END___ONEPURPLE____________________________________________________//

//_______________BEGIN___TWOPURPLE____________________________________________________//
void twoPurple(Adafruit_NeoPixel *strip) {
  for (int i = 0; i < 3; i++) {
    strip->setPixelColor(4,strip->Color(255, 0, 0));
    strip->show();
    delay(1000);
    strip->setPixelColor(4, 0);
    strip->show();
    delay(1000);
  }
    Serial.println("one Purple END");
}
//_______________END___TWOPURPLE____________________________________________________//

//_______________BEGIN___GHOST___________________________________________________//
void displayGhost() {
  //G
  stripBoard_R0.setPixelColor(15, stripBoard_R0.Color(255, 0, 0));
  stripBoard_R0.setPixelColor(16, stripBoard_R0.Color(255, 0, 0));
  stripBoard_R0.show();
  delay(1000);
  ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
  //H
  stripBoard_R0.setPixelColor(13, stripBoard_R0.Color(255, 0, 0));
  stripBoard_R0.setPixelColor(14, stripBoard_R0.Color(255, 0, 0));
  stripBoard_R0.show();
  delay(1000);
  ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
  //O
  stripBoard_R1.setPixelColor(25, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.setPixelColor(26, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.show();
  delay(1000);
  ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
  //S
  stripBoard_R1.setPixelColor(16, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.setPixelColor(17, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.show();
  delay(1000);
    ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
  //T
  stripBoard_R1.setPixelColor(14, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.setPixelColor(15, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.show();
  delay(1000);
  ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
}
//_______________END___GHOST________________________________________________//

//_______________BEGIN___CALLBACK___NEXTSP____________________________________________________//
void onCallback(byte* b,int length){
Serial.println("Callback called");
Serial.println((char)b[0]);
//String key = GetKey(b[0]);
//Serial.println("before onPurple call");
//onePurple(100, GetRow(key), key);
/*
  if(b[0] == '1') {
    Serial.println("YES ON");
    ledPatterns::fullWhite(50, &stripBoard_R4);
    ledPatterns::resetColor(LENGTH_BOARD_R4, &stripBoard_R4);
  }

  if(b[0] == '2') {
    Serial.println("Stern ON");
    ledPatterns::fullWhite(50, &stripBoard_R3);
    ledPatterns::resetColor(LENGTH_BOARD_R3, &stripBoard_R3);
  }

  if(b[0] == '3') {
    Serial.println("GOODBYE ON");
    ledPatterns::fullWhite(50, &stripBoard_R2);
    ledPatterns::resetColor(LENGTH_BOARD_R2, &stripBoard_R2);
  }

  if(b[0] == '4') {
    Serial.println("GOODBYE ON");
    ledPatterns::fullWhite(50, &stripBoard_R2);
    ledPatterns::resetColor(LENGTH_BOARD_R2, &stripBoard_R2);
  }*/

  /*if(b[0] == '1'){
    displayGhost();
  }*/
  //notReady = false;

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

    Serial.println("board setup ended");
  }*/
  //SETUP BOARD
  //R0
  pinMode(ledPIN_R0, OUTPUT);
  stripBoard_R0 = Adafruit_NeoPixel(LENGTH_BOARD_R0, ledPIN_R0, NEO_GRB + NEO_KHZ800);
  stripBoard_R0.begin();
  delay(100);
  //R1
  pinMode(ledPIN_R1, OUTPUT);
  stripBoard_R1 = Adafruit_NeoPixel(LENGTH_BOARD_R1, ledPIN_R1, NEO_GRB + NEO_KHZ800);
  stripBoard_R1.begin();
  delay(100);
  //R2
  pinMode(ledPIN_R2, OUTPUT);
  stripBoard_R2 = Adafruit_NeoPixel(LENGTH_BOARD_R2, ledPIN_R2, NEO_GRB + NEO_KHZ800);
  stripBoard_R2.begin();
  delay(100);
  //R3
  pinMode(ledPIN_R3, OUTPUT);
  stripBoard_R3 = Adafruit_NeoPixel(LENGTH_BOARD_R3, ledPIN_R3, NEO_GRB + NEO_KHZ800);
  stripBoard_R3.begin();
  delay(100);
  //R4
  pinMode(ledPIN_R4, OUTPUT);
  stripBoard_R4 = Adafruit_NeoPixel(LENGTH_BOARD_R4, ledPIN_R4, NEO_GRB + NEO_KHZ800);
  stripBoard_R4.begin();
  delay(100);
  //set all Colors to black
  ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
  ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
  ledPatterns::resetColor(LENGTH_BOARD_R2, &stripBoard_R2);
  ledPatterns::resetColor(LENGTH_BOARD_R3, &stripBoard_R3);
  ledPatterns::resetColor(LENGTH_BOARD_R4, &stripBoard_R4);

  Serial.println(GetID("208 97 210 131"));
  Serial.println(GetLength("208 97 210 131")+GetID("208 97 210 131"));
  Serial.println(GetID("68 197 208 131"));
  Serial.println(GetLength("68 197 208 131")+GetID("68 197 208 131"));
  Serial.println(GetID("70 199 167 131"));
  Serial.println(GetLength("70 199 167 131")+GetID("70 199 167 131"));

  Serial.println(GetID("171 253 130 195"));
  Serial.println(GetLength("171 253 130 195")+GetID("171 253 130 195"));
  Serial.println(GetID("77 245 130 195"));
  Serial.println(GetLength("77 245 130 195")+GetID("77 245 130 195"));
  Serial.println(GetID("227 154 131 195"));
  Serial.println(GetLength("227 154 131 195")+GetID("227 154 131 195"));

  Serial.println("End Setup");
}
//_____________________END__SETUP_______________________________________________________//

//_____________________BEGIN__LOOP______________________________________________________//
   void loop()
   {
     //onePurple(100, GetRow(key), key);

      //Serial.println("HI");
        //onePurple(500, &board::stripBoard_R0, "135 213 163 131");
        //twoPurple(&stripBoard_R0);
        //twoPurple(&stripBoard_R1);
        //twoPurple(&stripBoard_R2);
        //twoPurple(&stripBoard_R3);
        //twoPurple(&stripBoard_R4);
        //ledPatterns::fullWhite(100, &stripBoard_R0);

      /*
        ledPatterns::rainbow(5, &stripBoard_R0);
        ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
        ledPatterns::rainbow(5, &stripBoard_R1);
        ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
        ledPatterns::rainbow(5, &stripBoard_R2);
        ledPatterns::resetColor(LENGTH_BOARD_R2, &stripBoard_R2);
        ledPatterns::rainbow(5, &stripBoard_R3);
        ledPatterns::resetColor(LENGTH_BOARD_R3, &stripBoard_R3);
        ledPatterns::rainbow(5, &stripBoard_R4);
        ledPatterns::resetColor(LENGTH_BOARD_R4, &stripBoard_R4);
      */

        onePurple(100, GetRow("65 202 164 131"), "65 202 164 131");
        delay(100);
        onePurple(100, GetRow("135 213 163 131"), "135 213 163 131");
        delay(100);
        //displayGhost();
       //TURN LED ON WITH CAPACITIVE SENSOR
       /*if (!isActive){
       //loop capacitiveSensor
       pentagramm::loopCapacitiveSensor();
     }*/
     //Serial.println("Loop begin OUAHUUU");

     /*if (!isServer) {

     }*/

     /*if(!isServer){
       if (!ghostshown){
       displayGhost();
       ghostshown = true;
       Serial.println("Ghost was shown");
       }
     }*/
/*------WICHTIG________
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
    //ESP.getFreeHeap();
   //nextsp.update();
   //______WICHTIG*/
   //Serial.println("END LOOP");

}
//____________________________END____LOOP_____________________________________________//
