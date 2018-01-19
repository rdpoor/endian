#include "endian.h"

/**
 * A note on the ENDIAN_ORDER macro:
 *
 * Unless otherwise defined, ENDIAN_ORDER will be defined by the GCC compiler to
 * match the byte ordering of the target architecture.  In this case, the endian
 * library will use shortcuts when possible to avoid shuffling bytes.  If you 
 * want to test the non-shortcut code branches, un-comment the following line:
 */
// #define ENDIAN_ORDER NO_SHORTCUTS

#ifndef ENDIAN_ORDER
#define ENDIAN_ORDER __BYTE_ORDER__
#endif


uint8_t get_uint8_le(void *src) {
  return *COERCE_PTR(uint8_t, src);
}

uint8_t get_uint8_be(void *src) {
  return *COERCE_PTR(uint8_t, src);
}

uint16_t get_uint16_le(void *src) {
#if ENDIAN_ORDER == __ORDER_LITTLE_ENDIAN__
  uint16_t *v1 = COERCE_PTR(uint16_t, src);
  return *v1;
#else
  uint8_t *v1 = COERCE_PTR(uint8_t, src);
  uint16_t v2;
  v2 = (*v1++ & 0xff) << 0;
  v2 |= (*v1 & 0xff) << 8;
  return v2;
#endif
}

uint16_t get_uint16_be(void *src) {
#if ENDIAN_ORDER == __ORDER_BIG_ENDIAN__
  uint16_t *v1 = COERCE_PTR(uint16_t, src);
  return *v1;
#else
  uint8_t *v1 = COERCE_PTR(uint8_t, src);
  uint16_t v2;
  v2 = (*v1++ & 0xff) << 8;
  v2 |= (*v1 & 0xff) << 0;
  return v2;
#endif
}

uint32_t get_uint32_le(void *src) {
#if ENDIAN_ORDER == __ORDER_LITTLE_ENDIAN__
  uint32_t *v1 = COERCE_PTR(uint32_t, src);
  return *v1;
#else
  uint8_t *v1 = COERCE_PTR(uint8_t, src);
  uint32_t v2;
  v2 = (*v1++ & 0xff) << 0;
  v2 |= (*v1++ & 0xff) << 8;
  v2 |= (*v1++ & 0xff) << 16;
  v2 |= (*v1 & 0xff) << 24;
  return v2;
#endif
}

uint32_t get_uint32_be(void *src) {
#if ENDIAN_ORDER == __ORDER_BIG_ENDIAN__
  uint32_t *v1 = COERCE_PTR(uint32_t, src);
  return *v1;
#else
  uint8_t *v1 = COERCE_PTR(uint8_t, src);
  uint32_t v2;
  v2 = (*v1++ & 0xff) << 24;
  v2 |= (*v1++ & 0xff) << 16;
  v2 |= (*v1++ & 0xff) << 8;
  v2 |= (*v1 & 0xff) << 0;
  return v2;
#endif
}

uint64_t get_uint64_le(void *src) {
#if ENDIAN_ORDER == __ORDER_LITTLE_ENDIAN__
  uint64_t *v1 = COERCE_PTR(uint64_t, src);
  return *v1;
#else
  uint8_t *v1 = COERCE_PTR(uint8_t, src);
  uint64_t v2;
  v2 = ((uint64_t)(*v1++ & 0xff)) << 0;
  v2 |= ((uint64_t)(*v1++ & 0xff)) << 8;
  v2 |= ((uint64_t)(*v1++ & 0xff)) << 16;
  v2 |= ((uint64_t)(*v1++ & 0xff)) << 24;
  v2 |= ((uint64_t)(*v1++ & 0xff)) << 32;
  v2 |= ((uint64_t)(*v1++ & 0xff)) << 40;
  v2 |= ((uint64_t)(*v1++ & 0xff)) << 48;
  v2 |= ((uint64_t)(*v1 & 0xff)) << 56;
  return v2;
#endif
}

uint64_t get_uint64_be(void *src) {
#if ENDIAN_ORDER == __ORDER_BIG_ENDIAN__
  uint64_t *v1 = COERCE_PTR(uint64_t, src);
  return *v1;
#else
  uint8_t *v1 = COERCE_PTR(uint8_t, src);
  uint64_t v2;
  v2 = ((uint64_t)(*v1++ & 0xff)) << 56;
  v2 |= ((uint64_t)(*v1++ & 0xff)) << 48;
  v2 |= ((uint64_t)(*v1++ & 0xff)) << 40;
  v2 |= ((uint64_t)(*v1++ & 0xff)) << 32;
  v2 |= ((uint64_t)(*v1++ & 0xff)) << 24;
  v2 |= ((uint64_t)(*v1++ & 0xff)) << 16;
  v2 |= ((uint64_t)(*v1++ & 0xff)) << 8;
  v2 |= ((uint64_t)(*v1 & 0xff)) << 0;
  return v2;
#endif
}

float get_float_le(void *src) {
#if ENDIAN_ORDER == __ORDER_LITTLE_ENDIAN__
  return *COERCE_PTR(float, src);
#else
  uint32_t v1 = get_uint32_le(src);
  return *COERCE_PTR(float, &v1);
#endif
}

float get_float_be(void *src) {
#if ENDIAN_ORDER == __ORDER_BIG_ENDIAN__
  return *COERCE_PTR(float, src);
#else
  uint32_t v1 = get_uint32_be(src);
  return *COERCE_PTR(float, &v1);
#endif
}

double get_double_le(void *src) {
#if ENDIAN_ORDER == __ORDER_LITTLE_ENDIAN__
  return *COERCE_PTR(double, src);
#else
  uint64_t v1 = get_uint64_le(src);
  return *COERCE_PTR(double, &v1);
#endif
}  

double get_double_be(void *src) {
#if ENDIAN_ORDER == __ORDER_BIG_ENDIAN__
  return *COERCE_PTR(double, src);
#else
  uint64_t v1 = get_uint64_be(src);
  return *COERCE_PTR(double, &v1);
#endif
}

void put_uint8_le(void *dst, uint8_t v) {
  uint8_t *d = COERCE_PTR(uint8_t, dst);
  *d = v;
}

void put_uint8_be(void *dst, uint8_t v) {
  uint8_t *d = COERCE_PTR(uint8_t, dst);
  *d = v;
}  

void put_uint16_le(void *dst, uint16_t v) {
#if ENDIAN_ORDER == __ORDER_LITTLE_ENDIAN__
  uint16_t *d = COERCE_PTR(uint16_t, dst);
  *d = v;
#else
  uint8_t *d = COERCE_PTR(uint8_t, dst);
  *d++ = (v >> 0) & 0xff;
  *d = (v >> 8) & 0xff;
#endif
}
  
void put_uint16_be(void *dst, uint16_t v) {
#if ENDIAN_ORDER == __ORDER_BIG_ENDIAN__
  uint16_t *d = COERCE_PTR(uint16_t, dst);
  *d = v;
#else
  uint8_t *d = COERCE_PTR(uint8_t, dst);
  *d++ = (v >> 8) & 0xff;
  *d = (v >> 0) & 0xff;
#endif
}

void put_uint32_le(void *dst, uint32_t v) {
#if ENDIAN_ORDER == __ORDER_LITTLE_ENDIAN__
  uint32_t *d = COERCE_PTR(uint32_t, dst);
  *d = v;
#else
  uint8_t *d = COERCE_PTR(uint8_t, dst);
  *d++ = (v >> 0) & 0xff;
  *d++ = (v >> 8) & 0xff;
  *d++ = (v >> 16) & 0xff;
  *d = (v >> 24) & 0xff;
#endif
}

void put_uint32_be(void *dst, uint32_t v) {
#if ENDIAN_ORDER == __ORDER_BIG_ENDIAN__
  uint32_t *d = COERCE_PTR(uint32_t, dst);
  *d = v;
#else
  uint8_t *d = COERCE_PTR(uint8_t, dst);
  *d++ = (v >> 24) & 0xff;
  *d++ = (v >> 16) & 0xff;
  *d++ = (v >> 8) & 0xff;
  *d = (v >> 0) & 0xff;
#endif
}

void put_uint64_le(void *dst, uint64_t v) {
#if ENDIAN_ORDER == __ORDER_LITTLE_ENDIAN__
  uint64_t *d = COERCE_PTR(uint64_t, dst);
  *d = v;
#else
  uint8_t *d = COERCE_PTR(uint8_t, dst);
  *d++ = (v >> 0) & 0xff;
  *d++ = (v >> 8) & 0xff;
  *d++ = (v >> 16) & 0xff;
  *d++ = (v >> 24) & 0xff;
  *d++ = (v >> 32) & 0xff;
  *d++ = (v >> 40) & 0xff;
  *d++ = (v >> 48) & 0xff;
  *d = (v >> 56) & 0xff;
#endif
}

void put_uint64_be(void *dst, uint64_t v) {
#if ENDIAN_ORDER == __ORDER_BIG_ENDIAN__
  uint64_t *d = COERCE_PTR(uint64_t, dst);
  *d = v;
#else
  uint8_t *d = COERCE_PTR(uint8_t, dst);
  *d++ = (v >> 56) & 0xff;
  *d++ = (v >> 48) & 0xff;
  *d++ = (v >> 40) & 0xff;
  *d++ = (v >> 32) & 0xff;
  *d++ = (v >> 24) & 0xff;
  *d++ = (v >> 16) & 0xff;
  *d++ = (v >> 8) & 0xff;
  *d = (v >> 0) & 0xff;
#endif
}

void put_float_le(void *dst, float v) {
#if ENDIAN_ORDER == __ORDER_LITTLE_ENDIAN__
  float *d = COERCE_PTR(float, dst);
  *d = v;
#else
  uint32_t *v1 = COERCE_PTR(uint32_t, &v);
  put_uint32_le(dst, *v1);
#endif
}

void put_float_be(void *dst, float v) {
#if ENDIAN_ORDER == __ORDER_BIG_ENDIAN__
 float *d = COERCE_PTR(float, dst);
 *d = v;
#else
  uint32_t *v1 = COERCE_PTR(uint32_t, &v);
  put_uint32_be(dst, *v1);
#endif
}

void put_double_le(void *dst, double v) {
#if ENDIAN_ORDER == __ORDER_LITTLE_ENDIAN__
  double *d = COERCE_PTR(double, dst);
  *d = v;
#else
  uint64_t *v1 = COERCE_PTR(uint64_t, &v);
  put_uint64_le(dst, *v1);
#endif
}

void put_double_be(void *dst, double v) {
#if ENDIAN_ORDER == __ORDER_BIG_ENDIAN__
 double *d = COERCE_PTR(double, dst);
 *d = v;
#else
  uint64_t *v1 = COERCE_PTR(uint64_t, &v);
  put_uint64_be(dst, *v1);
#endif
}

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
  
  ASSERT(get_uint8_le((void *)a1) == 0x11);
  ASSERT(get_uint8_be((void *)a1) == 0x11);
  ASSERT(get_uint16_le((void *)a1) == 0x2211);
  ASSERT(get_uint16_be((void *)a1) == 0x1122);
  ASSERT(get_uint32_le((void *)a1) == 0x44332211);
  ASSERT(get_uint32_be((void *)a1) == 0x11223344);
  ASSERT(get_uint64_le((void *)a1) == 0x8877665544332211);
  ASSERT(get_uint64_be((void *)a1) == 0x1122334455667788);

  ASSERT(f_near(get_float_le((void *)a2le), f2));
  ASSERT(f_near(get_float_be((void *)a2be), f2));

  ASSERT(f_near(get_double_le((void *)a3le), d3));
  ASSERT(f_near(get_double_be((void *)a3be), d3));

  uint8_t *d[8];
  void *dst = (void *)d;
  
  put_uint8_le(dst, 0x01);
  ASSERT(get_uint8_le(dst) == 0x01);
  put_uint8_be(dst, 0x02);
  ASSERT(get_uint8_be(dst) == 0x02);
  put_uint16_le(dst, 0x0304);
  ASSERT(get_uint16_le(dst) == 0x0304);
  put_uint16_be(dst, 0x0506);
  ASSERT(get_uint16_be(dst) == 0x0506);
  put_uint32_le(dst, 0x0708090a);
  ASSERT(get_uint32_le(dst) == 0x0708090a);
  put_uint32_be(dst, 0x0b0c0d0e);
  ASSERT(get_uint32_be(dst) == 0x0b0c0d0e);
  put_uint64_le(dst, 0x0f10111213141516);
  ASSERT(get_uint64_le(dst) == 0x0f10111213141516);
  put_uint64_be(dst, 0x1718191a1b1c1d1e);
  ASSERT(get_uint64_be(dst) == 0x1718191a1b1c1d1e);

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
