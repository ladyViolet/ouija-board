namespace pentagramm {

//------CAPACITIVESENSOR-----//
// used a 510kOhm and 200kOhm between

const int sender = D3;
const int receiver = D6;
CapacitiveSensor cs_0_2 = CapacitiveSensor(sender, receiver); // D3 Sender, D2 Empfänger
unsigned long csSum;
bool isActive;

void loopCapacitiveSensor() {
  Serial.println("loop CapacitiveSensor");
  long sensor1 =  cs_0_2.capacitiveSensor(1);
    Serial.println(sensor1);  // print sensor output
     if(sensor1 >= 1000)
     {
       Serial.println("CapacitiveSensor activated");
       //if CapSensor is touched once, show Rainbow on LEDs
      ledPatterns::rainbow(20, &controller::strip_Controller);
      isActive = true;
      Serial.println("Rainbow called");
     }
   }
}
