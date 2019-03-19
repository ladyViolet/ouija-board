namespace ledPatterns {
//LED WHEEL
  // Input a value 0 to 255 to get a color value.
  // The colours are a transition r - g - b - back to r.
  uint32_t Wheel(byte WheelPos, Adafruit_NeoPixel *strip) {
    WheelPos = 255 - WheelPos;
    if(WheelPos < 85) {
      return strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if(WheelPos < 170) {
      WheelPos -= 85;
      return strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }

  void resetColor(int length, Adafruit_NeoPixel *strip) {
    for (int i=0; i<length;i++) {
      strip->setPixelColor(i, 0);
    }
    strip->show();
  }

//LED RAINBOW Pattern -- a bit slow to be used in callback
  void rainbow(uint32_t wait, Adafruit_NeoPixel *strip) {
    uint16_t i, j;
    for(j=0; j<256; j++) {
      for(i=0; i<strip->numPixels(); i++) {
        strip->setPixelColor(i, Wheel((i+j) & 255, strip));
      }
      strip->show();
      delay(wait);
    }
  }

//displays a purple wipe two times
  void colorWipe(uint8_t wait, Adafruit_NeoPixel *strip) {
      for(uint16_t i=0; i<strip->numPixels(); i++) {
        strip->setPixelColor(i, strip->Color(138,43,226));
        strip->show();
        delay(wait);
      }
  }

  void fullWhite(uint32_t wait, Adafruit_NeoPixel *strip) {
    for(uint16_t i=0; i<30; i++) {
          strip->setPixelColor(i, strip->Color(138,43,226));//blueviolet
      }
        strip->show();
        delay(wait);
        for(uint16_t i = 0; i < 30; i++) {
              strip->setPixelColor(i, 0);//black
          }
            strip->show();
            delay(wait);
            Serial.println("end full white");
  }

}
