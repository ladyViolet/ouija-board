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

//RFID-READER
int mode = 3;
//nExtSP
NEXTSP nextsp; //communication between Esp's
bool isServer;//if true --> Esp is Master
const int masterPIN = D0;//set to 5V to initialise Master
String sentData = "";//to avoid sending the same data again and again


//_______________BEGIN___GHOST________________________________________________//
void displayGhost() {
  //G
  stripBoard_R0.setPixelColor(15, stripBoard_R0.Color(255, 0, 0));
  stripBoard_R0.setPixelColor(16, stripBoard_R0.Color(255, 0, 0));
  stripBoard_R0.show();
  delay(500);
  ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
  //H
  stripBoard_R0.setPixelColor(13, stripBoard_R0.Color(255, 0, 0));
  stripBoard_R0.setPixelColor(14, stripBoard_R0.Color(255, 0, 0));
  stripBoard_R0.show();
  delay(500);
  ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
  //O
  stripBoard_R1.setPixelColor(25, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.setPixelColor(26, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.show();
  delay(500);
  ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
  //S
  stripBoard_R1.setPixelColor(16, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.setPixelColor(17, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.show();
  delay(500);
  ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
  //T
  stripBoard_R1.setPixelColor(14, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.setPixelColor(15, stripBoard_R1.Color(255, 0, 0));
  stripBoard_R1.show();
  delay(500);
  ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
}
//_______________END___GHOST__________________________________________________//

//_______________BEGIN___DISCO________________________________________________//
//FÜR ANDI
void playDisco() {
//D
stripBoard_R0.setPixelColor(21, stripBoard_R0.Color(0, 255, 220));
stripBoard_R0.setPixelColor(22, stripBoard_R0.Color(0, 255, 220));
stripBoard_R0.show();
delay(500);
ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
//I
stripBoard_R0.setPixelColor(11, stripBoard_R0.Color(0, 255, 220));
stripBoard_R0.setPixelColor(12, stripBoard_R0.Color(0, 255, 220));
stripBoard_R0.show();
delay(500);
ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
//S
stripBoard_R1.setPixelColor(16, stripBoard_R1.Color(0, 255, 220));
stripBoard_R1.setPixelColor(17, stripBoard_R1.Color(0, 255, 220));
stripBoard_R1.show();
delay(500);
ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
//C
stripBoard_R0.setPixelColor(23, stripBoard_R0.Color(0, 255, 220));
stripBoard_R0.setPixelColor(24, stripBoard_R0.Color(0, 255, 220));
stripBoard_R0.show();
delay(500);
ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
//O
stripBoard_R1.setPixelColor(25, stripBoard_R1.Color(0, 255, 220));
stripBoard_R1.setPixelColor(26, stripBoard_R1.Color(0, 255, 220));
stripBoard_R1.show();
delay(500);
ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
}
//_______________END___DISCO__________________________________________________//

//_______________BEGIN___CALLBACK___NEXTSP____________________________________//
void onCallback(byte* b,int length) {
Serial.println("Callback called");

  if(b[0] == '1') {
    Serial.println("YES ON");
    ledPatterns::colorWipe(50, &stripBoard_R4);
    ledPatterns::resetColor(LENGTH_BOARD_R4, &stripBoard_R4);
  }

  if(b[0] == '2') {
    Serial.println("Stern ON");
    ledPatterns::rainbow(5, &stripBoard_R3);
    ledPatterns::resetColor(LENGTH_BOARD_R3, &stripBoard_R3);
    playDisco();
  }

  if(b[0] == '4') {
    Serial.println("GOODBYE ON");
    displayGhost();
    delay(100);
    ledPatterns::colorWipe(5, &stripBoard_R2);
    ledPatterns::resetColor(LENGTH_BOARD_R2, &stripBoard_R2);
  }

  if (b[0] == 'A') {
    ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
    stripBoard_R0.setPixelColor(28, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.setPixelColor(29, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.show();
  }

  if (b[0] == 'B') {
    ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
    stripBoard_R0.setPixelColor(25, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.setPixelColor(26, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.show();
  }

  if (b[0] == 'C') {
    ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
    stripBoard_R0.setPixelColor(23, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.setPixelColor(24, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.show();
  }

  if (b[0] == 'D') {
    ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
    stripBoard_R0.setPixelColor(21, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.setPixelColor(22, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.show();
  }

  if (b[0] == 'E') {
    ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
    stripBoard_R0.setPixelColor(19, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.setPixelColor(20, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.show();
  }

  if (b[0] == 'F') {
    ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
    stripBoard_R0.setPixelColor(17, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.setPixelColor(18, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.show();
  }

  if (b[0] == 'G') {
    ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
    stripBoard_R0.setPixelColor(15, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.setPixelColor(16, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.show();
  }

  if (b[0] == 'H') {
    ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
    stripBoard_R0.setPixelColor(13, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.setPixelColor(14, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.show();
  }

  if (b[0] == 'I') {
    ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
    stripBoard_R0.setPixelColor(11, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.setPixelColor(12, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.show();
  }

  if (b[0] == 'J') {
    ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
    stripBoard_R0.setPixelColor(9, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.setPixelColor(10, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.show();
  }

  if (b[0] == 'K') {
    ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
    stripBoard_R0.setPixelColor(7, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.setPixelColor(8, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.show();
  }

  if (b[0] == 'L') {
    ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
    stripBoard_R0.setPixelColor(5, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.setPixelColor(6, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.show();
  }

  if (b[0] == 'M') {
    ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
    stripBoard_R0.setPixelColor(2, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.setPixelColor(3, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.setPixelColor(4, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.show();
  }

  if (b[0] == 'N') {
    ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
    stripBoard_R0.setPixelColor(0, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.setPixelColor(1, stripBoard_R0.Color(255, 0, 0));
    stripBoard_R0.show();
  }

  if (b[0] == 'O') {
    ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
    stripBoard_R1.setPixelColor(25, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.setPixelColor(26, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.show();
  }

  if (b[0] == 'P') {
    ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
    stripBoard_R1.setPixelColor(23, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.show();
  }

  if (b[0] == 'Q') {
    ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
    stripBoard_R1.setPixelColor(21, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.show();
  }

  if (b[0] == 'R') {
    ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
    stripBoard_R1.setPixelColor(18, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.setPixelColor(19, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.show();
    }

  if (b[0] == 'S') {
    ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
    stripBoard_R1.setPixelColor(16, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.setPixelColor(17, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.show();
    }

  if (b[0] == 'T') {
    ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
    stripBoard_R1.setPixelColor(14, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.setPixelColor(15, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.show();
    }

  if (b[0] == 'U') {
    ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
    stripBoard_R1.setPixelColor(12, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.setPixelColor(13, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.show();
  }

  if (b[0] == 'V') {
    ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
    stripBoard_R1.setPixelColor(10, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.setPixelColor(11, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.show();
  }

  if (b[0] == 'W') {
    ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
    stripBoard_R1.setPixelColor(7, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.setPixelColor(8, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.setPixelColor(9, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.show();
  }

  if (b[0] == 'X') {
    ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
    stripBoard_R1.setPixelColor(5, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.show();
  }

  if (b[0] == 'Y') {
    ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
    stripBoard_R1.setPixelColor(2, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.setPixelColor(3, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.show();
  }

  if (b[0] == 'Z') {
    ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
    stripBoard_R1.setPixelColor(0, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.setPixelColor(1, stripBoard_R1.Color(255, 0, 0));
    stripBoard_R1.show();
  }

  delay(500);
  Serial.println("Callback finished");
}
//_______________END___CALLBACK___NEXTSP______________________________________//

//_______________BEGIN___SETUP________________________________________________//
void setup() {

  Serial.begin(9600);
  Serial.flush();
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
  Serial.println("BOARD SETUP BEGIN");
    //INITIALIZE LED-STRIPS
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
    //set all strips to black
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
//_____________________END__SETUP_____________________________________________//

//_____________________BEGIN__LOOP____________________________________________//
   void loop()
   {
     Serial.println("Loop begin");
     //TURN LED ON WITH CAPACITIVE SENSOR

     if (isServer) {
       /*if (!isActive){
         pentagramm::loopCapacitiveSensor();
       }*/
       //GET KEY FROM RFID READER
       Serial.println(rfid().substring(1));
       String key = GetValue(rfid().substring(1));
       Serial.println(key);

    //ONLY SEND IF KEY IS EITHER EMPTY, NOR THE SAME AS BEFORE AND MAKE SURE ESP IS STILL CONNECTED
     if (nextsp.connected() && !key.equals(sentData) && !key.equals("EMPTY")) {
       sentData = key;
       Serial.println(sentData);

        if (key == "1") {
          controller::activateMotor();
        }

    nextsp.send(key);
    delay(100);
   }
  }
  delay(100);
  update_rfid();
  delay(100);
  nextsp.update();
   //Serial.println("END LOOP");
}
//________________END____LOOP_________________________________________________//
