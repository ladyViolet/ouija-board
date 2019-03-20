namespace controller {

//LED
const int ledPIN_Controller = D8;

//MOTOR
const int motorPin = D5; //Vibration on Controller

  void activateMotor() {
    digitalWrite(motorPin, HIGH);
    delay(1000);
    digitalWrite(motorPin, LOW);
  }
}
