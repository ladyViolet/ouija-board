namespace controller {

//LED
static const int LENGTH_CONTROLLER = 3;
const int ledPIN_Controller = D8;
CRGB strip_Controller[LENGTH_CONTROLLER];

//MOTOR
const int motorPin = D5; //Vibration on Controller

  void setupController() {
  //SETUP FOR SERVER
     pinMode(motorPin, OUTPUT);
     pinMode(ledPIN_Controller, OUTPUT);
     delay(100);
     FastLED.addLeds<NEOPIXEL, ledPIN_Controller>(strip_Controller, LENGTH_CONTROLLER);
     delay(100);

     Serial.println("end setupController");
  }

  void activateMotor() {
    digitalWrite(motorPin, HIGH);
    delay(200);
    digitalWrite(motorPin, LOW);
  }
}
