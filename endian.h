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
 * For pointer-to-pointer transfers, endian provides the MEMCPY_LE and MEMCPY_BE
 * macros:
 *
 * double d;
 * char buf[80]
 *
 * // copy double d into buf[4] as a little endian value
 * MEMCPY_LE(&buf[4], &d, sizeof(double))
 *
 * // copy double d into buf[4] as a big endian value
 * MEMCPY_BE(&buf[4], &d, sizeof(double))
 *
 * but it also provide a family of getters and putters:
 * 
 * double get_double_be(void *src);
 * double get_double_le(void *src);
 * void put_double_be(void *dst, double v);
 * void put_double_le(void *dst, double v);
 * ... etc ...
 */

// The __BYTE_ORDER__ compiler macro defines the byte ordering on the target
// CPU.  If it is little endian, little endian operations to use the native
// memcpy and use revcpy for big endian operations.  And vice versa for big
// endian CPUs.

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
void revcpy(void *dst, const void *src, int nbytes);

uint8_t get_uint8_t_le(void *src); // 'a needless consistancy...' :)
uint8_t get_uint8_t_be(void *src);

uint16_t get_uint16_t_le(void *src);
uint16_t get_uint16_t_be(void *src);

uint32_t get_uint32_t_le(void *src);
uint32_t get_uint32_t_be(void *src);

uint64_t get_uint64_t_le(void *src);
uint64_t get_uint64_t_be(void *src);

float get_float_le(void *src);
float get_float_be(void *src);

double get_double_le(void *src);
double get_double_be(void *src);


void put_uint8_t_le(void *dst, uint8_t v);
void put_uint8_t_be(void *dst, uint8_t v);

void put_uint16_t_le(void *dst, uint16_t v);
void put_uint16_t_be(void *dst, uint16_t v);

void put_uint32_t_le(void *dst, uint32_t v);
void put_uint32_t_be(void *dst, uint32_t v);

void put_uint64_t_le(void *dst, uint64_t v);
void put_uint64_t_be(void *dst, uint64_t v);

void put_float_le(void *dst, float v);
void put_float_be(void *dst, float v);

void put_double_le(void *dst, double v);
void put_double_be(void *dst, double v);

#endif
