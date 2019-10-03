#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>

#include "chapter2.h"

static inline void clear(void **addr) {
	if (*addr) { 
		free(*addr);
		*addr = NULL;
	}
}

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

TEST(tsub_ok_test) {
	ASSERT(tsub_ok(1, -1) == 1);
	ASSERT(tsub_ok(2147483647, -2147483648) == 0);
	ASSERT(tsub_ok(-2147483647, 2) == 0);
	ASSERT(tsub_ok(-2147483647, 1) == 1);
	ASSERT(tsub_ok(-1, 2147483647) == 1);

	return true;
}

TEST(calloc_test) {
	void *allocated = NULL;

	ASSERT((allocated = calloc_impl(0, 0)) == NULL); clear(&allocated);
	ASSERT((allocated = calloc_impl(0, 30)) == NULL); clear(&allocated);
	ASSERT((allocated = calloc_impl(30, 0)) == NULL); clear(&allocated);
	ASSERT((allocated = calloc_impl(5, 64)) != NULL); clear(&allocated);
	ASSERT((allocated = calloc_impl(1L<<63, 1L<<62)) == NULL); clear(&allocated);

	return true;
}

TEST(threefourth_test) {
	ASSERT(threefourth(4) == 3);
	ASSERT(threefourth(891) == 668);
	ASSERT(threefourth(2147483647) == 1610612735);
	ASSERT(threefourth(-4) == -3);
	ASSERT(threefourth(-891) == -668);
	ASSERT(threefourth(-2147483647) == -1610612735);
	ASSERT(threefourth(-2147483648) == -1610612736);

	return true;
}

TEST(fpwr2_test) {
	ASSERT(fpwr2(4) == 16.0f);
	ASSERT(fpwr2(5) == 32.0f);
	ASSERT(fpwr2(7) == 128.0f);
	ASSERT(fpwr2(-126 - 23) != 0.0f);
	ASSERT(fpwr2(-126 - 23 - 1) == 0.0f);
	ASSERT(fpwr2(127) != INFINITY);
	ASSERT(fpwr2(128) == INFINITY);
	
	printf("fpwr2(0) is %f.\n", fpwr2(0));
	printf("fpwr2(1) is %f.\n", fpwr2(1));
	printf("fpwr2(79) is %f.\n", fpwr2(79));

	return true;
}

/**
 * Apply changes here after modifying tests.
 */
size_t testc = 7;

test_function testv[] = {
	replace_byte_test,
	any_odd_one_test,
	int_size_is_32_test,
	tsub_ok_test,
	calloc_test,
	threefourth_test,
	fpwr2_test
};
