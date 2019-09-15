#include "test.h"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#include "chapter2.h"

TEST(replace_byte_test) { 
	// Only for little endian systems.
	ASSERT(replace_byte(0x12345678, 2, 0xAB) == 0x12AB5678);
	ASSERT(replace_byte(0x12345678, 0, 0xAB) == 0x123456AB);
	return true;
}

TEST(any_odd_one_test) {
	ASSERT(any_odd_one(0x00050000) == 1);
	ASSERT(any_odd_one(0xAAAAAAAA) == 0);
	return true;
}

TEST(int_size_is_32_test) {
	ASSERT(int_size_is_32() == 1);
	return true;
}

/**
 * Apply changes here after modifying tests.
 */
size_t testc = 3;

test_function testv[] = {
	replace_byte_test,
	any_odd_one_test,
	int_size_is_32_test
};
