#include "test.h"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#include "chapter3.h"

TEST(decode_test) { 
	ASSERT(decode2(1, 2, 3) == decode2(1, 2, 3));
	
	return true;
}

TEST(loop_test) {
	ASSERT(loop(0x12345678, 12) == loop(0x12345678, 12));

	return true;
}

TEST(cread_alt_test) {
	long num = 36;

	ASSERT(num == 36);
	ASSERT(cread_alt(&num) == 36);
	ASSERT(cread_alt(NULL) == 0);

	return true;
}

TEST(switch_prob_test) {
	ASSERT(switch_prob(20, 10) == 95);
	ASSERT(switch_prob(5, 66) == 80);
	
	return true;
}

/**
 * Apply changes here after modifying tests.
 */
size_t testc = 4;

test_function testv[] = {
	decode_test,
	loop_test,
	cread_alt_test,
	switch_prob_test
};
