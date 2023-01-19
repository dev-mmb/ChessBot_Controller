#include "Bitshift.hpp"

class Matrix 
{
public:
	Matrix(uint32_t latchPin = 10, uint32_t clockPin = 12, uint32_t dataPin = 11, uint32_t latchPin2 = 4, uint32_t clockPin2 = 6, uint32_t dataPin2 = 5) 
		: xShift(BitShift{latchPin, clockPin, dataPin}), yShift(BitShift{latchPin2, clockPin2, dataPin2})
	{}

	int read(uint8_t x, uint8_t y) 
	{
		byte xb =  ~(1 << x);
		byte yb =  (1 << y);
		xShift.write(xb);
		yShift.write(yb);
	}
private:
	const BitShift xShift, yShift;
};