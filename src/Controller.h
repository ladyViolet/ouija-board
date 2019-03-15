namespace controller {

//LED
const int ledPIN_Controller = D8;
Adafruit_NeoPixel strip_Controller;
static const int LENGTH_CONTROLLER = 8;//length of LED Strip

//MOTOR
const int motorPin = D5; //Vibration on Controller

  void setupController() {
  //SETUP FOR SERVER
     pinMode(motorPin, OUTPUT);

/*     Serial.println("1");
     pinMode(ledPIN_Controller, OUTPUT); //LED

     Serial.println("3");
     strip_Controller = Adafruit_NeoPixel(LENGTH_CONTROLLER, ledPIN_Controller, NEO_GRB + NEO_KHZ800);

     Serial.println("4");
     strip_Controller.begin();

     Serial.println("5");
     strip_Controller.setBrightness(50);

     Serial.println("6");
     strip_Controller.show();*/

     Serial.println("end setupController");
  }

  void activateMotor() {
    digitalWrite(motorPin, HIGH);
    delay(200);
    digitalWrite(motorPin, LOW);
  }
}
