#ifndef _chapter2
#define _chapter2

#include <stddef.h>

#define MSB(x)	\
((x) & (1 << ((sizeof(typeof(x)) << 3) - 1)) /* 0x1...0000 */)

#define IS_2_POWERED(x)	\
((((x) - 1) ^ (x)) == (((x) - 1) | (x)))

/* 2.60 */
unsigned replace_byte(unsigned x, int i, unsigned char b);

/* 2.64 */
int any_odd_one(unsigned x);

/* 2.67 */
int int_size_is_32();

/* 2.74 */
int tsub_ok(int x, int y);

/* 2.76 */
void *calloc_impl(size_t count, size_t size);

/* 2.80 */
int threefourth(int x);

/* 2.90 */
float fpwr2(int x);

#endif /* _chapter2 */
