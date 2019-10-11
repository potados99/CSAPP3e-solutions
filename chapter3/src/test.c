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

/**
 * Apply changes here after modifying tests.
 */
size_t testc = 2;

test_function testv[] = {
	decode_test,
	loop_test
};
