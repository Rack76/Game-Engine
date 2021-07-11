#pragma once

#include <stdint.h>

using Bitset = uint32_t;

class BitMask
{
public:
	BitMask() : bits(0) {}
	BitMask(const Bitset& bits) : bits(bits) {}

	Bitset getMask() const { return bits; }
	bool bitOn(const Bitset& bit) const { return bits & (1 << bit); }

	void setMask(const Bitset& bitset)  { bits = bitset; }
	void turnBitOn(const Bitset& bit);
	void turnBitsOn(const Bitset& bits);
	void clearBit(const Bitset& bit);
	void toggleBit(const Bitset& bit);
	void clear();

	bool matches(const BitMask& mask, const int& relevantBit = 64) const;
private:
	Bitset bits;
};