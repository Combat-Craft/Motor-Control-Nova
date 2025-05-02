#include "motor.h"

#define enc1 2
#define enc2 3
#define motorSpeed 11
#define motorDir1 10
#define motorDir2 9



//When the motor encode
float rpm = 0;
//For tracking RPM & ANALOG INPUT 
//int spd = 0;
//int cnt = 0;
Motor m(motorSpeed,motorDir1,motorDir2,enc1,enc2);
void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(enc2), countPulse, RISING);
  unsigned long currentTime = millis();
  m.update(currentTime);

}

//If C2 leads C1, opposite dir as if C1 leads C2 
void loop() {
  m.setSpeed(255);
  m.setDir('CCW');
  unsigned long currentTime = millis();
  if (currentTime - m.lastTime >= 1000) {
    noInterrupts();
    m.update(currentTime);
    interrupts();

}

//CODE FOR RPM & ANALOG INPUT
/*
if(m.lastTime/2000 > cnt){
  spd++;
  cnt++;
}

if(spd > 255){
  spd = 255;
  m.setSpeed(0);
  while(true);
}


Serial.print(spd);
Serial.print(",");
Serial.println(m.RPM);
delay(500);
}
*/

void countPulse() {
  m.pulseCount++;
}

void command(){
  Serial.println("----------------");
  Serial.println("Set speed ('sp')");
  Serial.println("Toggle output ('to')");
  Serial.println("Set direction ('sd')");
  Serial.println("Set Control Velocity ('cv')");
  Serial.println("----------------");
}
