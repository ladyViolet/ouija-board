namespace board {

Adafruit_NeoPixel stripBoard_R0;
Adafruit_NeoPixel stripBoard_R1;
Adafruit_NeoPixel stripBoard_R2;
Adafruit_NeoPixel stripBoard_R3;
Adafruit_NeoPixel stripBoard_R4;
//-----BOARD-----//
const int ledPIN_R0 = D5;
const int ledPIN_R1 = D7;
const int ledPIN_R2 = D8;
const int ledPIN_R3 = D2;
const int ledPIN_R4 = D1;
//LED ROWS ON TE BOARD (THEY'RE MARKED ON IT)
static const int LENGTH_BOARD_R0 = 30;
static const int LENGTH_BOARD_R1 = 27;
static const int LENGTH_BOARD_R2 = 22;
static const int LENGTH_BOARD_R3 = 27;
static const int LENGTH_BOARD_R4 = 9;
//-----END BOARD-----//

void setupBoard() {
    //SETUP LEDS FROM BOARD
      stripBoard_R0 = Adafruit_NeoPixel(LENGTH_BOARD_R0, ledPIN_R0, NEO_GRB + NEO_KHZ800);
      stripBoard_R1 = Adafruit_NeoPixel(LENGTH_BOARD_R1, ledPIN_R1, NEO_GRB + NEO_KHZ800);
      stripBoard_R2 = Adafruit_NeoPixel(LENGTH_BOARD_R2, ledPIN_R2, NEO_GRB + NEO_KHZ800);
      stripBoard_R3 = Adafruit_NeoPixel(LENGTH_BOARD_R3, ledPIN_R3, NEO_GRB + NEO_KHZ800);
      stripBoard_R4 = Adafruit_NeoPixel(LENGTH_BOARD_R4, ledPIN_R4, NEO_GRB + NEO_KHZ800);
      ledPatterns::resetColor(LENGTH_BOARD_R0, &stripBoard_R0);
      ledPatterns::resetColor(LENGTH_BOARD_R1, &stripBoard_R1);
      ledPatterns::resetColor(LENGTH_BOARD_R2, &stripBoard_R2);
      ledPatterns::resetColor(LENGTH_BOARD_R3, &stripBoard_R3);
      ledPatterns::resetColor(LENGTH_BOARD_R4, &stripBoard_R4);
      delay(100);
      //LED
         // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
        #if defined (__AVR_ATtiny85__)
          if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
        #endif
        // End of trinket special code
        pinMode(ledPIN_R0, OUTPUT);
        pinMode(ledPIN_R1, OUTPUT);
        pinMode(ledPIN_R2, OUTPUT);
        pinMode(ledPIN_R3, OUTPUT);
        pinMode(ledPIN_R4, OUTPUT);
        digitalWrite(ledPIN_R0, LOW);
        digitalWrite(ledPIN_R1, LOW);
        digitalWrite(ledPIN_R2, LOW);
        digitalWrite(ledPIN_R3, LOW);
        digitalWrite(ledPIN_R4, LOW);
        //ROW0
        stripBoard_R0.begin();
        stripBoard_R0.setBrightness(50);
        stripBoard_R0.show();
        //ROW1
        stripBoard_R1.begin();
        stripBoard_R1.setBrightness(50);
        stripBoard_R1.show();
        //ROW2
        stripBoard_R2.begin();
        stripBoard_R2.setBrightness(50);
        stripBoard_R2.show();
        //ROW3
        stripBoard_R3.begin();
        stripBoard_R3.setBrightness(50);
        stripBoard_R3.show();
        //ROW4
        stripBoard_R4.begin();
        stripBoard_R4.setBrightness(50);
        stripBoard_R4.show();
        //TEST
        delay(1000);
    }

}
