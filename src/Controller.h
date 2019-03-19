namespace controller {

//LED
const uint16_t LENGTH_CONTROLLER = 3;
const int ledPIN_Controller = D8;
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip_Controller(LENGTH_CONTROLLER, ledPIN_Controller);

//MOTOR
const int motorPin = D5; //Vibration on Controller

  void activateMotor() {
    digitalWrite(motorPin, HIGH);
    delay(1000);
    digitalWrite(motorPin, LOW);
  }
}
