#include "BitMask.h"

bool BitMask::matches(const BitMask& mask, const int& relevantBit) const
{
	return ((relevantBit < 64) ? (mask.getMask() & ( 1 << relevantBit)) == (this->bits & (1 << relevantBit)) : mask.getMask() == bits);
}

void BitMask::turnBitOn(const Bitset& bit)
{
	bits |= 1 << bit;
}

void BitMask::turnBitsOn(const Bitset& bits)
{
	this->bits |= bits;
}

void BitMask::clearBit(const Bitset& bit)
{
	bits &= ~(1 << bit);
}

void BitMask::toggleBit(const Bitset& bit)
{
	bits ^= 1 << bit;
}

void BitMask::clear()
{
	bits = 0;
}