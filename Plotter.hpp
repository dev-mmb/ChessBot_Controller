#include <Servo.h>
#include "Axis.hpp"

class Plotter {
    Axis xAxis, yAxis;
    Servo servo;
    void enableMagnet() {
      servo.write(180);
      delay(magnetDelay);
    }
    void disableMagnet() {
      servo.write(0);
      delay(magnetDelay);
    }
    int16_t getNearestLane(int16_t tile) {
      return (tileWidth * tile) + getLaneOffset();
    }
    int16_t getLaneOffset() {
      return tileWidth / 2;
    }
    void resetZero() {
      moveAxes(-200, -200);
      xAxis.setCurrentPosition(0);
      yAxis.setCurrentPosition(0);
    }
    void moveOffBoard() {
      moveAxes(3400, 3300);
    }
  public:
    static const int16_t boardXOffset = 400;
    static const int16_t boardYOffset = 400;
    static const int16_t tileWidth = 200;
    static const int16_t asciiLowerCaseOffset = 'a' - 1;
    static const int16_t magnetDelay = 1000;
    static const int16_t plotterDelay = 500;

    Plotter(Axis& x, Axis& y, Servo& _servo) : xAxis(x), yAxis(y), servo(_servo) { }
    void moveAxes(int16_t x, int16_t y, bool xFirst = true) {
      if (xFirst) {
        xAxis.goToPosition(x);
        yAxis.goToPosition(y);
      } else {
        yAxis.goToPosition(y);
        xAxis.goToPosition(x);
      }
    }
    void uciInstruction(String uci) {
      // Does not support promotions
      String halfOne = uci.substring(0, 2);
      String halfTwo = uci.substring(2, 4);

      // Any time input is used boardOffset must be applied to calculated coordinate
      int16_t xInputOne = int(halfOne.charAt(0) - asciiLowerCaseOffset);
      int16_t xTargetOne = xInputOne * tileWidth + boardXOffset;
      int16_t yInputOne = int(halfOne.charAt(1) - '0');
      int16_t yTargetOne = yInputOne * tileWidth + boardYOffset;

      int16_t xInputTwo = int(halfTwo.charAt(0) - asciiLowerCaseOffset);
      int16_t xTargetTwo = xInputTwo * tileWidth + boardXOffset;
      int16_t yInputTwo = int(halfTwo.charAt(1) - '0');
      int16_t yTargetTwo = yInputTwo * tileWidth + boardYOffset;

      // Clear any existing pieces in second tile of UCI instruction
      // e.g A1B1 -> clear B1
      // TODO: Add check to see if clearing necessary?
      // Magnet is first disabled to prevent servo moving to the 90deg position on first instruction
      disableMagnet();
      moveAxes(xTargetTwo, yTargetTwo);
      enableMagnet();
      // Move to Y lane to avoid interfering with other pieces
      moveAxes(xTargetTwo, getNearestLane(yInputTwo) + boardYOffset, true);
      delay(plotterDelay);
      // Move Piece off of board via Y lane
      moveOffBoard();
      disableMagnet();

      // Move to first tile in UCI instruction and turn on magnet
      // e.g: A1B1 -> move to A1 -> enable magnet
      moveAxes(xTargetOne, yTargetOne);
      enableMagnet();
      // Move piece at first tile in UCI instruction to second tile via lanes
      // e.g: A1B1 -> move piece at A1 to B1 while not passing through other tiles

      // Move piece to closest lane from start position
      // e.g A1B1 -> move to A1 closest lane
      moveAxes(getNearestLane(xInputOne) + boardXOffset, getNearestLane(yInputOne) + boardYOffset);
      delay(plotterDelay);

      // Move to destination closest lane
      // Y Axis moved first
      moveAxes(getNearestLane(xInputTwo) + boardXOffset, getNearestLane(yInputTwo) + boardYOffset, true);
      delay(plotterDelay);

      // Move to destination target X, lane Y
      // Pieces moved to destination via the Y axis, as in, the plotter is moved to the target X coordinate,
      // but is still in the Y axis lane. The piece is moved into position via the Y axis.
      moveAxes(xTargetTwo, getNearestLane(yInputTwo) + boardYOffset);
      delay(plotterDelay);
      // Move piece to target via Y axis and disable magnet, return to zero

      // Commented out to fix pieces overshooting their target position by movement of the magnet servo.
      //moveAxes(xTargetTwo, yTargetTwo, true);
      //delay(plotterDelay);
      disableMagnet();

      // Zero is reset to maintain consistency in case of belt slip.
      resetZero();
    }
};