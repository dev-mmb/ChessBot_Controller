#include "Matrix.hpp"
#include "Plotter.hpp"
int readpin = A1;

Matrix matrix{readpin};
Plotter* plotter;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(readpin, INPUT_PULLUP);

  Axis xA(2, 3);
  Axis yA(4, 5);
  const int16_t MAGNET_PIN = 9;

  Servo servo;
  servo.attach(MAGNET_PIN);
  plotter = new Plotter(yA, xA, servo);

}

void loop() {
    for (int y = 0; y < 8; y++) {
      for (int x = 0; x < 8; x++) {
        int v = matrix.read(x, y);
        Serial.print((v < 400) ? " # " :  " . ");
        Serial.print("   ");
        delay(4);
      }
      Serial.println();
    }
   Serial.println("-----------------------------------------");
   delay(50);

   square(*plotter);

   
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
