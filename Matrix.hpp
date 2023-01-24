#include "Bitshift.hpp"
#include "Board.hpp"

// latchPin = Blue
// clockPin = Yellow
// dataPin = Orange
class Matrix 
{
public:
	//Matrix(uint32_t readpin, uint32_t latchPin = 10, uint32_t clockPin = 12, uint32_t dataPin = 11, uint32_t latchPin2 = 6, uint32_t clockPin2 = 8, uint32_t dataPin2 = 7) 
	//	: xShift(BitShift{latchPin, clockPin, dataPin}), yShift(BitShift{latchPin2, clockPin2, dataPin2}), readpin{readpin}
	Matrix(uint32_t readpin, uint32_t latchPin = 10, uint32_t clockPin = 12, uint32_t dataPin = 11, uint32_t latchPin2 = 6, uint32_t clockPin2 = 8, uint32_t dataPin2 = 7) 
		: xShift(BitShift{latchPin, clockPin, dataPin}), yShift(BitShift{latchPin2, clockPin2, dataPin2}), readpin{readpin}
	
	{}

	
	int read(uint8_t x, uint8_t y) 
	{
		byte xb = (1 << x);
		byte yb = ~ (1 << y);
		xShift.write(xb);
		yShift.write(yb);
		return analogRead(readpin);
	}

	void readBoard(Board& board) {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				board.setTile(x, y, read(x, y) < comprval);
				delay(7);
			}
		}
		delay(50);
	}

	void print() {
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				Serial.print((read(x, y) < comprval) ? "# " : ". ");
				delay(7);
			}
			Serial.println();
		}
		Serial.println("----------------------------------------------"); 
	}

	uint32_t getXLatchPin() const { 
		return xShift.getLatchPin();
	}
	uint32_t getYLatchPin() const { 
		return yShift.getLatchPin();
	}
	uint32_t getYClockPin() const { 
		return yShift.getClockPin();
	}
	uint32_t getXClockPin() const { 
		return xShift.getClockPin();
	}
	uint32_t getXDataPin() const { 
		return xShift.getDataPin();
	}
	uint32_t getYDataPin() const { 
		return yShift.getDataPin();
	}
private:
	const BitShift xShift, yShift;
	const uint32_t readpin;
	const int comprval = 400;
};
