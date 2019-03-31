/*
 * Using a shif-register to control a 7 segment display.
 * 
 */

// 2D array for snake load animation.
int loadSnake [8] [8] = {
  { 0, 0, 0, 0, 0, 0, 0, 1 },
  { 0, 0, 0, 0, 0, 0, 1, 0 },
  { 0, 0, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 1, 0, 0, 0, 0, 0, 0 },
  { 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0 }
};

// 2D array for numbers 0 - 9.
int segNumbers [10] [8]{
  { 1, 1, 0, 1, 1, 1, 1, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0 },
  { 1, 1, 0, 1, 0, 1, 1, 1 },
  { 0, 1, 0, 1, 1, 1, 0, 1 },
  { 0, 0, 0, 1, 1, 0, 1, 1 },
  { 0, 1, 0, 1, 0, 1, 1, 1 },
  { 1, 1, 0, 1, 0, 0, 1, 1 },
  { 0, 0, 0, 1, 1, 1, 0, 0 },
  { 1, 1, 0, 1, 1, 1, 1, 1 },
  { 0, 0, 0, 1, 1, 1, 1, 1 },
}; 

const int dataPin = 2;
const int outEn = 3;
const int latchPin = 4;
const int clockPin = 5;  // Moves bit into register.
const int reset = 6;
const int serOut = 7;

int displayNum;
int shiftClk = 0;
const long timeDelay = 0;
unsigned long prevMillis = 0;


void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(outEn, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(reset, OUTPUT);
  pinMode(serOut, INPUT);

  Serial.begin(9600);

}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= timeDelay) {

    prevMillis = currentMillis;
    
    SegAnimation();

    
  }

}

void SegAnimation() {
  // Function that runs different animations on the display.

  digitalWrite(reset, LOW);
  digitalWrite(reset, HIGH);
  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      
      if (loadSnake [i] [j] == 1) {
        digitalWrite(dataPin, HIGH);
        digitalWrite(clockPin, HIGH);
      
      }
      else {
        digitalWrite(dataPin, LOW);
        digitalWrite(clockPin, HIGH);
      }
      digitalWrite(clockPin, LOW);
      //Serial.print(loadSnake [i] [j]);
      delay(5);
      
    }
    
    digitalWrite(latchPin, HIGH);
    //Serial.println();
    
    digitalWrite(dataPin, LOW);
    digitalWrite(clockPin, LOW);
    digitalWrite(latchPin, LOW);
    
  }
  
}

