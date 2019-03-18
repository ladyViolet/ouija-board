namespace board {
//-----BOARD-----//
//LED ROWS ON TE BOARD (THEY'RE MARKED ON IT)
static const int LENGTH_BOARD_R0 = 30;
static const int LENGTH_BOARD_R1 = 27;
static const int LENGTH_BOARD_R2 = 22;
static const int LENGTH_BOARD_R3 = 27;
static const int LENGTH_BOARD_R4 = 9;

const int ledPIN_R0 = D5;
const int ledPIN_R1 = D7;
const int ledPIN_R2 = D8;
const int ledPIN_R3 = D2;
const int ledPIN_R4 = D1;

CRGB stripBoard_R0[LENGTH_BOARD_R0];
CRGB stripBoard_R1[LENGTH_BOARD_R1];
CRGB stripBoard_R2[LENGTH_BOARD_R2];
CRGB stripBoard_R3[LENGTH_BOARD_R3];
CRGB stripBoard_R4[LENGTH_BOARD_R4];
//-----END BOARD-----//

void setupBoard() {
    //SETUP LEDS FROM BOARD
      pinMode(ledPIN_R0, OUTPUT);
      pinMode(ledPIN_R1, OUTPUT);
      pinMode(ledPIN_R2, OUTPUT);
      pinMode(ledPIN_R3, OUTPUT);
      pinMode(ledPIN_R4, OUTPUT);
      delay(100);

      FastLED.addLeds<NEOPIXEL, ledPIN_R0>(stripBoard_R0, LENGTH_BOARD_R0);
      FastLED.addLeds<NEOPIXEL, ledPIN_R1>(stripBoard_R1, LENGTH_BOARD_R1);
      FastLED.addLeds<NEOPIXEL, ledPIN_R2>(stripBoard_R2, LENGTH_BOARD_R2);
      FastLED.addLeds<NEOPIXEL, ledPIN_R3>(stripBoard_R3, LENGTH_BOARD_R3);
      FastLED.addLeds<NEOPIXEL, ledPIN_R4>(stripBoard_R4, LENGTH_BOARD_R4);
      delay(100);
    }

}
