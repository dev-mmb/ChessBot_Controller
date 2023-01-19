#include "Matrix.hpp"

// ZWARTE KANT VAN DE DIODE MOET NAAR DE HAL SENSOR WIJZEN!!!!!


//Pin connected to ST_CP of 74HC595
int latchPin = 10;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
//Pin connected to DS of 74HC595
int dataPin = 11;

int readpin = A1;

Matrix matrix;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(readpin, INPUT_PULLUP);

}

void loop() {
    for (int y = 0; y < 8; y++) {
      for (int x = 0; x < 8; x++) {
        matrix.read(x, y);
        int v = analogRead(readpin);
        Serial.print((v < 400) ? " # " :  " . ");
        Serial.print("   ");
        delay(4);
      }
      Serial.println();
    }
   Serial.println("-----------------------------------------");
   delay(50);
}
