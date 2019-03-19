namespace board {
//LED ROWS ON TE BOARD (THEY'RE MARKED ON IT)
const uint16_t LENGTH_BOARD_R0 = 30;
const uint16_t LENGTH_BOARD_R1 = 27;
const uint16_t LENGTH_BOARD_R2 = 22;
const uint16_t LENGTH_BOARD_R3 = 27;
const uint16_t LENGTH_BOARD_R4 = 9;

const int ledPIN_R0 = D5;
const int ledPIN_R1 = D7;
const int ledPIN_R2 = D8;
const int ledPIN_R3 = D2;
const int ledPIN_R4 = D1;

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> stripBoard_R0(LENGTH_BOARD_R0, ledPIN_R0);
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> stripBoard_R1(LENGTH_BOARD_R1, ledPIN_R1);
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> stripBoard_R2(LENGTH_BOARD_R2, ledPIN_R2);
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> stripBoard_R3(LENGTH_BOARD_R3, ledPIN_R3);
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> stripBoard_R4(LENGTH_BOARD_R4, ledPIN_R4);
//-----BOARD-----//


//-----END BOARD-----//

}
