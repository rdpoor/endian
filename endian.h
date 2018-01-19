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
