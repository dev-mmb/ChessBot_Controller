class BitShift 
{
public:
	BitShift(uint32_t latchPin, uint32_t clockPin, uint32_t dataPin) 
		: latchPin(latchPin), dataPin(dataPin), clockPin(clockPin)
	{
		
	}

	void write(byte v) const
	{
		digitalWrite(latchPin, 0);
		shiftOut(dataPin, clockPin, MSBFIRST, v);
		digitalWrite(latchPin, 1);
	}

	uint32_t getLatchPin() const {
		return latchPin;
	}

	uint32_t getClockPin() const {
		return clockPin;
	}

	uint32_t getDataPin() const {
		return dataPin;
	}
private:
	const uint32_t latchPin, clockPin, dataPin;
};
