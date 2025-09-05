#include <gAlg.h>

#include "stdint.h"



uint32_t gAlg_XorShift32(uint32_t x)
{
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;

	return x;
}



uint32_t gAlg_Murmur3Mix(uint32_t k)
{
	k ^= k >> 16;
	k *= 0x85ebca6b;
	k ^= k >> 13;
	k *= 0xc2b2ae35;
	k ^= k >> 16;

	return k;
}