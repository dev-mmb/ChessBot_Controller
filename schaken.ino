#include "Matrix.hpp"

//Pin connected to ST_CP of 74HC595
int latchPin = 10;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
//Pin connected to DS of 74HC595
int dataPin = 11;

Matrix matrix;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);

}

void loop() {
    for (int x = 0; x < 2; x++) {
      for (int y = 0; y < 2; y++) {
        matrix.read(x, y);
        delay(100);
      }
    }
   
}
