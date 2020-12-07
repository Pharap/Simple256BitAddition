#pragma once

// Released under CC0

inline uint8_t addBytes(uint8_t * destination, const uint8_t * leftSource, const uint8_t * rightSource, size_t size, uint8_t carryBit = 0)
{
	for(size_t index = 0; index < size; ++index)
	{
		// By using uint16_t the carry bit will end up in the upper byte
		uint16_t sum = leftSource[index] + rightSource[index] + carryBit;
		
		// Extract the lower bit (i.e. the sum modulo 256)
		destination[index] = static_cast<uint8_t>(sum);
		
		// Extract the carry bit (i.e. the low bit of the upper byte)
		carryBit = (sum >> 8);
	}
	
	// Return the carry bit
	return carryBit;
}

template<size_t size>
inline uint8_t addBytes(uint8_t (&destination)[size], const uint8_t (&leftSource)[size], const uint8_t (&rightSource)[size], uint8_t carryBit = 0)
{
	return addBytes(&destination, &leftSource, &rightSource, size, carryBit);
}

inline uint8_t addBytesInPlace(uint8_t * destination, const uint8_t * source, size_t size, uint8_t carryBit = 0)
{
	for(size_t index = 0; index < size; ++index)
	{
		// By using uint16_t the carry bit will end up in the upper byte
		uint16_t sum = destination[index] + source[index] + carryBit;
		
		// Extract the lower bit (i.e. the sum modulo 256)
		destination[index] = static_cast<uint8_t>(sum);
		
		// Extract the carry bit (i.e. the low bit of the upper byte)
		carryBit = (sum >> 8);
	}
	
	// Return the carry bit
	return carryBit;
}

template<size_t size>
inline uint8_t addBytesInPlace(uint8_t (&destination)[size], const uint8_t (&source)[size], uint8_t carryBit = 0)
{
	return addBytesInPlace(&destination, &source, size, carryBit);
}

struct Int256
{
	uint8_t bytes[32];
};

inline Int256 operator +(const Int256 & left, const Int256 & right)
{
	Int256 result;
	addBytes(result.bytes, left.bytes, right.bytes);
	return result;
}

inline Int256 & operator +=(Int256 & left, const Int256 & right)
{
	addBytesInPlace(result.bytes, left.bytes, right.bytes);
	
	return left;
}