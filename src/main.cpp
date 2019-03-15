#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "LedPatterns.h"
#include "nExtSP.h"
#include "CapacitiveSensor.h"
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

bool AS_oncesent;

//RFID-READER
int mode = 3;
//nExtSP
NEXTSP nextsp; //communication between Esp's
bool isServer;//if true Esp is Master
const int masterPIN = D0;//set to 5V to initialise Master
String sentData = "ANDERS";//to avoid sending the same data again and again

//_______________BEGIN___ONEPURPLE____________________________________________________//
void onePurple(uint8_t wait, Adafruit_NeoPixel *strip, String key) {
  Serial.println("OnePurple");
  for(int i = GetID(key); i <= GetLength(key); i++) {
        strip->setPixelColor(i, strip->Color(148,0,211) );//dark purple
    }
      strip->show();
      delay(wait);
      Serial.println("DarkPurple");
      ledPatterns::resetColor(GetLength(key), strip);
}
//_______________END___ONEPURPLE____________________________________________________//

//_______________BEGIN___GHOST___________________________________________________//
void displayGhost() {
  //G
  stripBoard_R0.setPixelColor(15, stripBoard_R0.Color(255, 0, 0));
  stripBoard_R0.setPixelColor(16, stripBoard_R0.Color(255, 0, 0));
  stripBoard_R0.show();
  delay(1000);
  stripBoard_R0.setPixelColor(15, stripBoard_R0.Color(0, 0, 0));
  stripBoard_R0.setPixelColor(16, stripBoard_R0.Color(0, 0, 0));
  stripBoard_R0.show();
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
  stripBoard_R1.show();
  //S
  stripBoard_R1.setPixelColor(16, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.setPixelColor(17, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.show();
  delay(1000);
  stripBoard_R1.setPixelColor(16, stripBoard_R1.Color(0, 0, 0));
  stripBoard_R1.setPixelColor(17, stripBoard_R1.Color(0, 0, 0));
  stripBoard_R1.show();
  //T
  stripBoard_R1.setPixelColor(14, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.setPixelColor(15, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.show();
  delay(1000);
  stripBoard_R1.setPixelColor(15, stripBoard_R1.Color(0, 0, 0));
  stripBoard_R1.show();
}
//_______________END___GHOST________________________________________________//

//_______________BEGIN___CALLBACK___NEXTSP____________________________________________________//
void onCallback(byte* b,int length){
Serial.println("Callback called");
//Serial.println(b[0], HEX);
//String key = GetKey(b[0]);
//Serial.println("before onPurple call");
//onePurple(20, GetRow(key), key);
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
  
  if(b[0] == '1'){
    displayGhost();
  }
  delay(100);
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
  nextsp.begin(isServer,"OUIIIJAAA",&onCallback);
  delay(100);
  Serial.println("after esp begin");

    while(!nextsp.connected())
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
  }


  Serial.println("End Setup");
}
//_____________________END__SETUP_______________________________________________________//

//_____________________BEGIN__LOOP______________________________________________________//
   void loop()
   {
       //TURN LED ON WITH CAPACITIVE SENSOR
       /*if (!isActive){
       //loop capacitiveSensor
       pentagramm::loopCapacitiveSensor();
     }*/
     Serial.println("Loop begin");
     /*if (!isServer) {
       ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
       ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
       ledPatterns::resetColor(LENGTH_BOARD_R2, &stripBoard_R2);
       ledPatterns::resetColor(LENGTH_BOARD_R3, &stripBoard_R3);
       ledPatterns::resetColor(LENGTH_BOARD_R4, &stripBoard_R4);
       Serial.println("Colors reset");
     }*/

     /*if(!isServer){
       if (!ghostshown){
       displayGhost();
       ghostshown = true;
       Serial.println("Ghost was shown");
       }
     }*/

     //String key = "DERP";//rfid().substring(1);
     String key = rfid().substring(1);

     Serial.println(key);
     if (isServer && nextsp.connected() && !key.equals(sentData)) {
         sentData = GetValue(key);
         Serial.println(sentData);

         if (!GetValue(key).equals("EMPTY")) {
            //ledPatterns::resetColor(LENGTH_CONTROLLER, &strip_Controller);
            Serial.println("000");

            if (GetValue(key) == "1") {
              controller::activateMotor();
              Serial.println("444");
            }


            // AS vermutlich noch doof
            nextsp.send('1');

            Serial.println("222");
            delay(50);
            Serial.println("333");
            
        }

        delay(20);
        Serial.println("555");
        update_rfid();

   }
    Serial.println("666");
    // geht laut elisa auch ohne
    delay(100);
    
    nextsp.update();
   Serial.println("END LOOP");

}
//____________________________END____LOOP_____________________________________________//
