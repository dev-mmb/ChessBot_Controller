
class BitShift 
{
public:
	BitShift(uint32_t latchPin, uint32_t clockPin, uint32_t dataPin) 
		: latchPin(latchPin), dataPin(dataPin), clockPin(clockPin)
	{
		pinMode(latchPin, OUTPUT);
		pinMode(dataPin, OUTPUT);
		pinMode(clockPin, OUTPUT);
	}

	void write(byte v) const
	{
		digitalWrite(latchPin, 0);
		shiftOut(dataPin, clockPin, MSBFIRST, v);
		digitalWrite(latchPin, 1);
	}
private:
	const uint32_t latchPin, clockPin, dataPin;
};