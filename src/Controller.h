namespace controller {

//LED
const int ledPIN_Controller = D8;
Adafruit_NeoPixel strip_Controller;
static const int LENGTH_CONTROLLER = 3;//length of LED Strip

//MOTOR
const int motorPin = D5; //Vibration on Controller

  void activateMotor() {
    digitalWrite(motorPin, HIGH);
    delay(1000);
    digitalWrite(motorPin, LOW);
  }
}
