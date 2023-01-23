#include <Servo.h>

class Axis {
    uint32_t dirPin, stepPin;
    int16_t currentPosition;
  public:
    static const int16_t speed = 800;


    Axis(uint32_t dp, uint32_t sp) {
      dirPin = dp;
      stepPin = sp;
    }
    uint32_t getDirPin() const {
      return dirPin;
    }
    uint32_t getStepPin() const {
      return stepPin;
    }

    int16_t getCurrentPosition() {
      return currentPosition;
    }
    void setCurrentPosition(int16_t curpos) {
      currentPosition = curpos;
    }
    void goToPosition(int16_t target) {
      Serial.print("stepPin: ");
      Serial.print(stepPin);
      Serial.print(", dirPin: ");
      Serial.println(dirPin);
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