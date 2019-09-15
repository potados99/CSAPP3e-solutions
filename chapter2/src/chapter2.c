#include "chapter2.h"

/**
 * 2.60
 * Change a byte at specific index i in x, with b.
 *
 * @param x	the source to be changed.
 * @param i	index of byte to change in x.
 * @param b	the replacement.
 *
 * @return	the result after the replacement, or the original x if the i is out of range.
 */
unsigned replace_byte(unsigned x, int i, unsigned char b) {
	if (i < 0 || i > sizeof(unsigned) - 1) {
		// Conversion from int to size_t is safe.
		// i will always be positive when evaluating the expression at the right.
		return x;
	}

	unsigned char *target = (unsigned char *)&x + (unsigned)i;
	*target = b;

	return x;
}

/**
 * 2.64
 * Check if the given integer has any odd bits.
 * Assume that integer width is 32.
 *
 * @param x	the target to determine.
 *
 * @return	non-zero if any odd bits, or zero.
 */
int any_odd_one(unsigned x) {
	return !(!(x & 0x55555555));
}

/**
 * 2.67
 * Check if this machine has 32 bits of int size.
 *
 * Implementation limit: No use of sizeof.
 *
 * @return	non-zero if size of int is 32, or zero.
 */
int int_size_is_32() {	
	int set_msb = 1 << 15 << 15 << 1;
	int beyond_msb = set_msb << 1;

	return set_msb && !beyond_msb;
}
