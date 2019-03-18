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
bool notReady;//to avoid blocking data
const int masterPIN = D0;//set to 5V to initialise Master
String sentData = "";//to avoid sending the same data again and again


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
void onCallback(byte* b,int length) {
Serial.println("Callback called");
Serial.println((char)b[0]);

  if(b[0] == '1') {
    Serial.println("YES ON");
    ledPatterns::rainbow(5, &stripBoard_R4);
    ledPatterns::resetColor(LENGTH_BOARD_R4, &stripBoard_R4);
  }

  if(b[0] == '2') {
    Serial.println("Stern ON");
    ledPatterns::rainbow(5, &stripBoard_R3);
    ledPatterns::resetColor(LENGTH_BOARD_R3, &stripBoard_R3);
  }

/*  if(b[0] == '3') {
    Serial.println("GOODBYE ON");
    ledPatterns::rainbow(5, &stripBoard_R2);
    ledPatterns::resetColor(LENGTH_BOARD_R2, &stripBoard_R2);
  }*/

  if(b[0] == '4') {
    Serial.println("GOODBYE ON");
    ledPatterns::rainbow(5, &stripBoard_R2);
    ledPatterns::resetColor(LENGTH_BOARD_R2, &stripBoard_R2);
  }

  /*if(b[0] == '1'){
    displayGhost();
  }*/
  Serial.println(notReady);
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
  nextsp.begin(isServer,"OUIIIJAAA",&onCallback);
  delay(100);
  Serial.println("after esp begin");

    while(!nextsp.connected())
    {
        Serial.print(".");
        nextsp.update();
        delay(100);
    }

  //SERVER
  if(isServer){
  //SETUP CONTROLLER
    //MOTOR
    pinMode(motorPin, OUTPUT);
    //LED
    pinMode(ledPIN_Controller, OUTPUT);
    strip_Controller = Adafruit_NeoPixel(LENGTH_CONTROLLER, ledPIN_Controller, NEO_GRB + NEO_KHZ800);
    strip_Controller.begin();
    strip_Controller.show();
    Serial.println("end setupController");
    Serial.println("controller setup ended");
    //CAPACITIVESENSOR
    cs_0_2.set_CS_AutocaL_Millis(0xFFFFFFFF);// turn off autocalibrate on channel 1 - just as an example
    Serial.println("SetupCapa");
    //RFID READER
    setup_rfid();
    Serial.println("setup rfid success");
  }

  //CLIENT
  if(!isServer){
  //SETUP BOARD
    //R0
    Serial.println("BOARD SETUP BEGIN");

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

    Serial.println("board setup ended");
  }
  controller::activateMotor();
  Serial.println("End Setup");
}
//_____________________END__SETUP_______________________________________________________//

//_____________________BEGIN__LOOP______________________________________________________//
   void loop()
   {
     Serial.println("Loop begin OUAHUUU");
     Serial.printf("not Ready im loop" ); Serial.println(notReady);
      /*FOR TESTING
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

       //TURN LED ON WITH CAPACITIVE SENSOR
       /*if (!isActive){
       //loop capacitiveSensor
       pentagramm::loopCapacitiveSensor();
     }*/

     /*if(!isServer){
       if (!ghostshown){
       displayGhost();
       ghostshown = true;
       Serial.println("Ghost was shown");
       }
     }*/

     //String key = "DERP";//rfid().substring(1);
     if (isServer) {

       Serial.println(rfid().substring(1));
       String key = GetValue(rfid().substring(1));
       Serial.println(key);



      while (!nextsp.connected()){
        Serial.printf("x");
      }

     if (nextsp.connected() && !key.equals(sentData) && !key.equals("EMPTY")) {
         sentData = key;
         Serial.println(sentData);

            //ledPatterns::resetColor(LENGTH_CONTROLLER, &strip_Controller);
            Serial.println("000");
            if (key == "1") {
              controller::activateMotor();
              Serial.println("444");
            }
          // AS vermutlich noch doof

          nextsp.send(key);
          delay(100);
          //  Serial.println("111");
   }
  }
  delay(100);
  update_rfid();
  //Serial.println("222");
  // geht laut elisa auch ohne
  delay(100);
  nextsp.update();
   //Serial.println("END LOOP");

}
//____________________________END____LOOP_____________________________________________//
