#include "motor.h"

#define enc1 2
#define enc2 3
#define motorSpeed 11
#define motorDir1 10
#define motorDir2 9



//When the motor encode
float rpm = 0;
Motor m(motorSpeed,motorDir1,motorDir2,enc1,enc2);
void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(enc2), countPulse, RISING);
  attachInterrupt(digitalPinToInterrupt(enc1), countPulse, RISING);
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
    Serial.println("RPM: ");
    Serial.println(m.RPM);
    interrupts();

}
}


void countPulse() {
  m.pulseCount++;
}
