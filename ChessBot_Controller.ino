#include <Servo.h>
#include "Matrix.hpp"
#include "Plotter.hpp"
int readpin = A1;
int resetPin = 16;

Matrix matrix{readpin};
Plotter* plotter;

Board fst, snd;
bool usingFst = false;
bool resetState = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  const int16_t MAGNET_PIN = 9;
  Servo servo;
  servo.attach(MAGNET_PIN);
  plotter = new Plotter(4, 5, 2, 3, servo);

  pinMode(plotter->getXDirPin(), OUTPUT);
  pinMode(plotter->getXStepPin(), OUTPUT);
  pinMode(plotter->getYDirPin(), OUTPUT);
  pinMode(plotter->getYStepPin(), OUTPUT);

  pinMode(matrix.getXLatchPin(), OUTPUT);
  pinMode(matrix.getYLatchPin(), OUTPUT);
  pinMode(matrix.getXClockPin(), OUTPUT);
  pinMode(matrix.getYClockPin(), OUTPUT);
  pinMode(matrix.getXDataPin(), OUTPUT);
  pinMode(matrix.getYDataPin(), OUTPUT);
  pinMode(readpin, INPUT_PULLUP);

  pinMode(resetPin, INPUT_PULLUP);
}

void loop() {  
  String inp;

  //matrix.print();
  //delay(700);
  //return;
  
  matrix.readBoard(fst);
  usingFst = false;
  while (Serial.available() == 0) {
    if (!resetState && digitalRead(resetPin)) {
      resetState = true;
      Serial.print("reset\r\n");
    } else if (resetState && !digitalRead(resetPin)) {
      resetState = false;
    }
    
    Board& prev = usingFst ? snd : fst;
    Board& current = usingFst ? fst : snd;
    //Serial.print("Using buffer ");
    //Serial.println(usingFst ? "fst" : "snd");
    usingFst = !usingFst;

    Change change;
    matrix.readBoard(current);
    if (current.difference(prev, change)) {
      Serial.print(change.toString() + "\r\n");
      Serial.flush();
      break;
    }
  }


  inp = Serial.readString();
  inp.trim();
  if (inp.length() == 4) {
    plotter->uciInstruction(inp);
  } else {
    int delim = inp.indexOf(',');
    int x = atoi(inp.substring(0, delim).c_str());
    int y = atoi(inp.substring(delim + 1, inp.length()).c_str());
    //Serial.print("Moving to ");
    //Serial.print(x);
    //Serial.print(", ");
    //Serial.println(y);
    plotter->moveAxes(x, y);
  }
}

void circle(Plotter& plotter) {
  int STEP_COUNT = 30;
  int CIRCLE_RADIUS = 800;
  int MARGIN = 400;
  float RPS = 1.0f;
  for (float angle = 0.0f; angle < PI * 2; angle += PI * 2.0f / STEP_COUNT) {
    int x = cos(angle) * CIRCLE_RADIUS + CIRCLE_RADIUS + MARGIN;
    int y = sin(angle) * CIRCLE_RADIUS + CIRCLE_RADIUS + MARGIN;

    plotter.moveAxes(x, y);
    delay(RPS * 1000.0f / STEP_COUNT);
  }
}

void square(Plotter& plotter) {
  int MIN = 800;
  int MAX = 2400;
  plotter.moveAxes(MIN, MIN);
  delay(100);
  plotter.moveAxes(MAX, MIN);
  delay(100);
  plotter.moveAxes(MAX, MAX);
  delay(100);
  plotter.moveAxes(MIN, MAX);
  delay(100);
}

void zeroMe(Plotter& plt) {
  plt.moveAxes(-400, -400);
}
