/**
MIT License

Copyright (c) 2018 Robert Poor <rdpoor at gmail etc>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "endian.h"
#include <stdint.h>
#include <string.h>

// The __BYTE_ORDER__ compiler macro defines the byte ordering on the target
// CPU.  If it is little endian, we define little endian operations to use the
// native memcpy and to revcpy for big endian operations.  And vice versa for
// big endian CPUs.

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define MEMCPY_LE memcpy
#define MEMCPY_BE revcpy
#else
#define MEMCPY_LE revcpy
#define MEMCPY_BE memcpy
#endif

/**
 * revcpy is like memcpy but with byte reversal
 */
void revcpy(void *dst, const void *src, int nbytes) {
  uint8_t *d = dst;
  const uint8_t *s = src;
  
  d += nbytes;
  while (nbytes--) {
    *--d = *s++;
  }
}

// special case the one-byte operations
uint8_t get_int8_t_be(const void *src) { return *(int8_t *)src; }
uint8_t get_int8_t_le(const void *src) { return *(int8_t *)src; }
uint8_t get_uint8_t_be(const void *src) { return *(uint8_t *)src; }
uint8_t get_uint8_t_le(const void *src) { return *(uint8_t *)src; }

void put_int8_t_be(void *dst, int8_t v) { *(int8_t *)dst = v; }
void put_int8_t_le(void *dst, int8_t v) { *(int8_t *)dst = v; }
void put_uint8_t_be(void *dst, uint8_t v) { *(uint8_t *)dst = v; }
void put_uint8_t_le(void *dst, uint8_t v) { *(uint8_t *)dst = v; }

#define MAKE_GETTER_PUTTER(type)            \
  type get_##type##_be(const void *src) {         \
    type v;                                 \
    MEMCPY_BE(&v, src, sizeof(type));       \
    return v;                               \
  }                                         \
  type get_##type##_le(const void *src) {         \
    type v;                                 \
    MEMCPY_LE(&v, src, sizeof(type));       \
    return v;                               \
  }                                         \
  void put_##type##_be(void *dst, type v) { \
    MEMCPY_BE(dst, &v, sizeof(type));       \
  }                                         \
  void put_##type##_le(void *dst, type v) { \
    MEMCPY_LE(dst, &v, sizeof(type));       \
  }

MAKE_GETTER_PUTTER(double)
MAKE_GETTER_PUTTER(float)
MAKE_GETTER_PUTTER(int16_t)
MAKE_GETTER_PUTTER(int32_t)
MAKE_GETTER_PUTTER(int64_t)
MAKE_GETTER_PUTTER(uint16_t)
MAKE_GETTER_PUTTER(uint32_t)
MAKE_GETTER_PUTTER(uint64_t)

// =============================================================================
// UNIT TESTING
// To compile for unit testing:
//    cc -Wall -DUNIT_TEST -o endian endian.c

#ifdef UNIT_TEST

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define ASSERT(expr) if (!(expr)) a_failed(__FILE__, __LINE__, #expr)

void a_failed(char *file, int line, char *expr) {
  fprintf(stderr, "%s:%d: assertion failed: %s\n", file, line, expr);
}

bool f_near(double a, double b) {
  return fabs((a - b)/b) < 0.01;
}

int main() {
  uint8_t a1[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};

  // bit pattern for float 1.058301
  float f2 = 1.058301;
  uint8_t a2le[] = {0x65, 0x76, 0x87, 0x3f};
  uint8_t a2be[] = {0x3f, 0x87, 0x76, 0x65};

  // bit pattern for double 1.066928
  double d3 = 1.066928;
  uint8_t a3le[] = {0x67, 0x56, 0x45, 0x34, 0x23, 0x12, 0xf1, 0x3f};
  uint8_t a3be[] = {0x3f, 0xf1, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67};

  fprintf(stderr, "Starting endian tests...\n");

  ASSERT(get_uint8_t_le((void *)a1) == 0x11);
  ASSERT(get_uint8_t_be((void *)a1) == 0x11);
  ASSERT(get_int16_t_le((void *)a1) == 0x2211);
  ASSERT(get_int16_t_be((void *)a1) == 0x1122);
  ASSERT(get_uint16_t_le((void *)a1) == 0x2211);
  ASSERT(get_uint16_t_be((void *)a1) == 0x1122);
  ASSERT(get_int32_t_le((void *)a1) == 0x44332211);
  ASSERT(get_int32_t_be((void *)a1) == 0x11223344);
  ASSERT(get_uint32_t_le((void *)a1) == 0x44332211);
  ASSERT(get_uint32_t_be((void *)a1) == 0x11223344);
  ASSERT(get_int64_t_le((void *)a1) == 0x8877665544332211);
  ASSERT(get_int64_t_be((void *)a1) == 0x1122334455667788);
  ASSERT(get_uint64_t_le((void *)a1) == 0x8877665544332211);
  ASSERT(get_uint64_t_be((void *)a1) == 0x1122334455667788);

  ASSERT(f_near(get_float_le((void *)a2le), f2));
  ASSERT(f_near(get_float_be((void *)a2be), f2));

  ASSERT(f_near(get_double_le((void *)a3le), d3));
  ASSERT(f_near(get_double_be((void *)a3be), d3));

  uint8_t *d[8];
  void *dst = (void *)d;

  put_uint8_t_le(dst, 0x01);
  ASSERT(get_uint8_t_le(dst) == 0x01);
  put_uint8_t_be(dst, 0x02);
  ASSERT(get_uint8_t_be(dst) == 0x02);

  put_int16_t_le(dst, 0x0304);
  ASSERT(get_int16_t_le(dst) == 0x0304);
  put_int16_t_be(dst, 0x0506);
  ASSERT(get_int16_t_be(dst) == 0x0506);

  put_uint16_t_le(dst, 0x0304);
  ASSERT(get_uint16_t_le(dst) == 0x0304);
  put_uint16_t_be(dst, 0x0506);
  ASSERT(get_uint16_t_be(dst) == 0x0506);

  put_int32_t_le(dst, 0x0708090a);
  ASSERT(get_int32_t_le(dst) == 0x0708090a);
  put_int32_t_be(dst, 0x0b0c0d0e);
  ASSERT(get_int32_t_be(dst) == 0x0b0c0d0e);

  put_uint32_t_le(dst, 0x0708090a);
  ASSERT(get_uint32_t_le(dst) == 0x0708090a);
  put_uint32_t_be(dst, 0x0b0c0d0e);
  ASSERT(get_uint32_t_be(dst) == 0x0b0c0d0e);

  put_int64_t_le(dst, 0x0f10111213141516);
  ASSERT(get_int64_t_le(dst) == 0x0f10111213141516);
  put_int64_t_be(dst, 0x1718191a1b1c1d1e);
  ASSERT(get_int64_t_be(dst) == 0x1718191a1b1c1d1e);

  put_uint64_t_le(dst, 0x0f10111213141516);
  ASSERT(get_uint64_t_le(dst) == 0x0f10111213141516);
  put_uint64_t_be(dst, 0x1718191a1b1c1d1e);
  ASSERT(get_uint64_t_be(dst) == 0x1718191a1b1c1d1e);

  put_float_le(dst, f2);
  ASSERT(f_near(get_float_le(dst), f2));
  put_float_be(dst, f2);
  ASSERT(f_near(get_float_be(dst), f2));

  put_double_le(dst, d3);
  ASSERT(f_near(get_double_le(dst), d3));
  put_double_be(dst, d3);
  ASSERT(f_near(get_double_be(dst), d3));

  fprintf(stderr, "...finished endian tests.\n");
}

#endif // #ifdef UNIT_TEST
