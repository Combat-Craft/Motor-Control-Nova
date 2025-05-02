#include <Arduino.h>
#ifndef MOTOR
#define MOTOR

class Motor{
    public:
        //class variables
        bool controlMode = 0; //All motor objects are intialized with control mode turned off
        int EnPin,dirAPin, dirBPin, encAPin, encBPin; //Intializing pins for arduino implementation
        float RPM;
        unsigned long lastTime = 0;
        volatile long pulseCount = 0;
        long count = 0;


        //PID Constants
        float ki = 1.0;
        float kp = 1.0;
        float kd = 1.0;
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
          if(controlMode == 0){
            analogWrite(EnPin,speed);
          }
          else{
            analogWrite(EnPin,0);
          }

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
        void update(unsigned long currentTime){ //updates RPM value, in .ino file, make sure to run thais in conditional block for every amount of secs
            //
                long count = pulseCount;
                pulseCount = 0;
                RPM = (count/204.0)*60.0;
                lastTime = currentTime;
        }
        void toggleControl(){
            if(controlMode == 0){
              controlMode = 1;
            }
            else{
              controlMode = 0;
            }
        }
        void setTargetVelocity(float input, float output){
            Serial.println("Buttpoop");
        }
};
#endif


