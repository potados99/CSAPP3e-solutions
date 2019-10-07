#include "chapter2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

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

/**
 * Check if overflow/underflow occurs after adding y to x.
 *
 * If the x and the y has different sign, it will never happen
 * because the absolute value of the result will get smaller.
 *
 * If two have the same sign, we can determine if the overflow happened by
 * checking the result:
 * After the operation, if the result has an oppsite sign to the opperand,
 * it is the case the overflow took its place.
 */
static inline int tadd_ok(int x, int y) {
	return (MSB(x) != MSB(y) || MSB(x + y) == MSB(x));
}

/**
 * 2.74 
 * Determine whether arguments can be subtracted without overflow.
 *
 * We can use the tadd_ok logic but under condition that y and -y is not same.
 * There is one case the condition not met: T_MIN, in binary 0x1000..0000
 *
 * @param x	left operand.
 * @param y right operand.
 *
 * @return 	non-zero if ok; otherwise zero.
 */
int tsub_ok(int x, int y) {
	return (y != (1 << 31) && tadd_ok(x, -y));
}

/**
 * Check if overflow occurs after multiplying x by y.
 *
 * Key idea 1: x*y > k if and only if x > k/y.
 * Key idea 2: evaluation of (x*y)/y will not be the same as x if overflow occurs.
 *
 * The first method needs k, which is 1<<(sizeof(size_t)<<3) - 1, which will generate warning.
 */
static inline int size_t_mult_ok(size_t x, size_t y) {
	return (x == 0 || (x*y)/x == y);
}

/**
 * 2.76
 * Mock calloc function in the standard library.
 * 
 * This function would not be bound to bit width of size_t
 * and be free from arithmetic overflow error.
 *
 * @param count	number of elements to allocate.
 * @param size	size of each element to allocate.
 *
 * @return		the allocated address if succedded; otherwise NULL.
 */
void *calloc_impl(size_t count, size_t size) {
	if (!(count && size)) {
		// Not an error.
		return NULL;
	}

	if (!size_t_mult_ok(count, size)) {
		// Definitely an error.
		errno = ENOMEM;
		return NULL;
	}

	size_t alloc_size = count * size;
	void *allocated = malloc(alloc_size);

	if (allocated == NULL) {
		// Error in malloc.
		return NULL;
	}

	if (memset(allocated, 0, alloc_size) == NULL) {
		// Error in memset.
		return NULL;
	}

	return allocated;
}

/** 
 * 2.80
 * Evaluate (3/4)x and round toward zero.
 *
 * Divide first and multiply later to prevent overflow.
 * The key idea is to correct the lose.
 *
 * @param x	the operand.
 *
 * @return	(3/4)x evaluated.
 */
int threefourth(int x) {
	// x/4 + x/2 = (3/4)x.
	int raw = (x >> 2) + (x >> 1);

	// 0x01 is truncated by both 1/4 and 3/4
	int bias = x & 0x01;
 
	return raw + bias;
}

static inline float u2f(unsigned x) {
  return *((float *)&x);
}

/**
 * 2.90
 * Evaluate 2^x.
 *
 * We use IEEE single precision floating point representation. 
 *
 * Length of each field is:
 * 	Sign: 						1
 * 	Exponent: 					8
 * 	Fragment: 					23
 *
 * Characteristics:
 * 	Bias:						127		
 * 	Normalized exponent range: 	[-126, 127]
 *
 * @param x		power.
 *
 * @return		the result in single-precision floating point representation.
 *				return zero if x is too small, +oo if x is too big.
 */
float fpwr2(int x) {
	/* Result exponent and fraction */
	unsigned exp;
  	unsigned frac;
  	unsigned u;

  	if (x < -126 /* Minimun denormailzed exponent value */ + 
			-23 /* Length of fraction to represent the smallest number */) {
   		/* too small. return 0.0 */
   		exp = 0;
    	frac = 0;
  	} else if (x < -126 /* Minumum denormalized exponent value. */) {
  	 	/* Denormalized result */
  		exp = 0;
  		frac = 1 << (unsigned)(23 /* Length of fragment */ + x + 126 /* Min exponent * -1 */);
  	} else if (x < 128 /* Maximum normalized exponent value + 1. */) {
  		/* Normalized result */
  	 	exp = 127 /* Bias */ + x;
  	 	frac = 0;
  	} else {
  	 	/* Too big, return +oo */
  	 	exp = 0xFF;
  	 	frac = 0;
  	}

  	/* Pack exp and frac into 32 bits */
  	u = exp << 23 | frac;
  	/* Result as float */
  	return u2f(u);
}
