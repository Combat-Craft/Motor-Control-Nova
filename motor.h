#include <Arduino.h>
#ifndef MOTOR
#define MOTOR

class Motor{
    public:
        //class variables
        bool controlMode = 0;
        int EnPin,dirAPin, dirBPin, encAPin, encBPin; //Intializing pins for arduino implementation
        float RPM;
        unsigned long lastTime = 0;
        volatile long pulseCount = 0;
        long count = 0;
        //init__ constructor
        Motor(int EnPin, int dirAPin, int dirBpin, int encAPin, int encBPin){
            this->EnPin = EnPin;
            this->dirAPin = dirAPin;
            this->dirBPin = dirBpin;
            this->encAPin = encAPin;
            this->encBPin = encBPin;
            pinMode(this->EnPin,OUTPUT);
            pinMode(this->dirAPin, OUTPUT);
            pinMode(this->dirBPin, OUTPUT);
            pinMode(this->encAPin, INPUT_PULLUP);
            pinMode(this->encBPin, INPUT_PULLUP);
            digitalWrite(this->dirAPin, HIGH); //Setting both dir pins to HIGH makes sure the motor doesn't run
            digitalWrite(this->dirBPin, HIGH); //on Motor obj intialization

        }
        
        //Functionality methods
        void setSpeed(int speed){
            analogWrite(EnPin,speed);
        }
        void setDir(char dir[]){ //CW or CCW are the only valid inputs
                if(dir == 'CW'){
                    digitalWrite(dirAPin,HIGH);
                    digitalWrite(dirBPin,LOW);
                }
                else if(dir == 'CCW'){
                    digitalWrite(dirAPin,LOW);
                    digitalWrite(dirBPin,HIGH);
                }
                else{
                    Serial.println("Error: Either use CW or CWW");   
                }
            }
        void update(unsigned long currentTime){ //updates RPM value, in .ino file, make sure to run this in conditional block for every amount of secs
            //
                long count = pulseCount;
                pulseCount = 0;
                Serial.println(count);
                RPM = (count/204.0)*60.0;
                lastTime = currentTime;
        }
        void toggleControl(bool arg){
            controlMode = arg;
        }
};
#endif


