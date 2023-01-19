#include <Servo.h>

class Axis {
    int16_t currentPosition, dirPin, stepPin;
  public:
    static const int16_t speed = 800;

    Axis (int16_t dp, int16_t sp) {
      dirPin = dp;
      stepPin = sp;
      pinMode(stepPin, OUTPUT);
      pinMode(dirPin, OUTPUT);
    }
    int16_t getCurrentPosition() {
      return currentPosition;
    }
    void setCurrentPosition(int16_t curpos) {
      currentPosition = curpos;
    }
    void goToPosition(int16_t target) {
      if (currentPosition == target) return;

      else if (currentPosition < target) {
        digitalWrite(dirPin, HIGH);
        for (int i = 0; i < target - currentPosition; i++) {
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(speed);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(speed);
        }
      }
      else {
        digitalWrite(dirPin, LOW);
        for (int i = 0; i < currentPosition - target; i++) {
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(speed);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(speed);
        }
      }
      currentPosition = target;
    }
};