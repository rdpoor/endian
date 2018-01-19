/**
 * endian: a byte-ordering library.
 */
#ifndef _ENDIAN_H
#define _ENDIAN_H

#include <stdint.h>

/**
 * COERCE_PTR(type, p) 
 *
 * @param type a C language type
 * @param p    a pointer to some storage (register or memory)
 *
 * @note
 * The COERCE_PTR macro allows you to cast a pointer of an arbitrary C type to
 * any other C pointer type. For example:
 *
 *     float f;
 *     uint32_t i = *COERCE_PTR(uint32_t, &f)
 *     printf("Bit pattern for %f is 0x%x\n", f, i);
 *
 * Alternatively:
 *
 *     float f;
 *     uint32_t *i = COERCE_PTR(uint32_t, &f)
 *     printf("Bit pattern for %f is 0x%x\n", f, *i);
 */
#define COERCE_PTR(type, v) ((type *)v)

uint8_t get_uint8_le(void *src); // 'a needless consistancy...' :)
uint8_t get_uint8_be(void *src);

uint16_t get_uint16_le(void *src);
uint16_t get_uint16_be(void *src);

uint32_t get_uint32_le(void *src);
uint32_t get_uint32_be(void *src);

uint64_t get_uint64_le(void *src);
uint64_t get_uint64_be(void *src);

float get_float_le(void *src);
float get_float_be(void *src);

double get_double_le(void *src);
double get_double_be(void *src);


void put_uint8_le(void *dst, uint8_t v);
void put_uint8_be(void *dst, uint8_t v);

void put_uint16_le(void *dst, uint16_t v);
void put_uint16_be(void *dst, uint16_t v);

void put_uint32_le(void *dst, uint32_t v);
void put_uint32_be(void *dst, uint32_t v);

void put_uint64_le(void *dst, uint64_t v);
void put_uint64_be(void *dst, uint64_t v);

void put_float_le(void *dst, float v);
void put_float_be(void *dst, float v);

void put_double_le(void *dst, double v);
void put_double_be(void *dst, double v);

#endif
