#include "test.h"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

TEST(compile_test) { 
	// Define your tests...
	ASSERT(sizeof(long) == 8);
	return true;
}

/**
 * Apply changes here after modifying tests.
 */
size_t testc = 1;

test_function testv[] = {
	compile_test
};
