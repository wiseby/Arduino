#include <Arduino.h>

const int encoderInterrupt = 3;
const int encoderPinA = 4;
const int encoderPinB = 5;

volatile int stateEncoderA = 0;
volatile int stateEncoderB = 0;

int QEM [16] = {0,-1,1,2,1,0,2,-1,-1,2,0,1,2,1,-1,0}; // Encoder Matrix for direction translation.
int stateEncoderInterrupt = 0;
int out;
int printTime = 100;

float encoderTick = 0;
float currentTime;
float prevPrintTime;

byte currState = 0b0000000;
byte prevState = 0b0000000;

void setup() {
  attachInterrupt(digitalPinToInterrupt(encoderInterrupt), EncoderHandler, CHANGE);
  Serial.begin(9600);
}

void loop() {
  if(millis() - prevPrintTime >= printTime){
    Serial.print("\tTick: ");
    Serial.println(int(encoderTick));
    prevPrintTime = millis();
  }
  prevState = currState;
  currState = stateEncoderA * 2 + stateEncoderB;

  out = QEM[prevState * 4 + currState];


  if(out == 1){
    encoderTick += 0.25;
  }
  else if(out == -1){
    encoderTick -= 0.25;
  }
}

void EncoderHandler(){
  stateEncoderA = digitalRead(encoderPinA);
  stateEncoderB = digitalRead(encoderPinB);
}
