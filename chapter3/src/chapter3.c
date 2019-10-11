#include "chapter3.h"

/**
 * Implemented from given assembly:
 *
 *	decode2:
 *		subq	%rdx, %rsi
 *		imulq	%rsi, %rdi
 *		movq	%rsi, %rax
 *		salq	$63, %rax
 *		sarq	$63, %rax
 *		xorq	%rdi, %rax
 *		ret
 *
 * x in %rdi, y in %rsi, z in %rdx
 */
long decode2(long x, long y, long z) {
	long temp;

	y = y - z;
	x = x * y;
	temp = y;
	temp = temp << 63;
	temp = temp >> 63;
	temp = temp ^ x;

	return temp;
}

/**
 * Retrieved from assembly.
 */
long loop(long x, int n) {
	long result = 0;
	long mask;
	for (mask = 1; mask != 0; mask <<= n) {
		result |= (x & mask);
	}
	return result;
}
