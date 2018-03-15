# endian
`endian` is a collection of byte-order aware routines written in C.  Unlike stream-oriented libraries that depend on a user-supplied method for reading and writing bytes, endian is optimized for reading from and writing between pointers in memory.

## Sample Usage

    #include "endian.h"
    #include <stdio.h>
    
    int main() {
      uint8_t bytes[] = {0x11, 0x22, 0x33, 0x44};
      printf("Interpreted as a little-endian byte stream, bytes = 0x%x\n", get_uint32_t_le((void *)bytes));
      printf("Interpreted as a big-endian byte stream, bytes = 0x%x\n", get_uint32_t_be((void *)bytes));
      return 0;
    }

`endian` also provides two macros, MEMCPY_LE and MEMCPY_BE, which are ideal when you need to move data between two memory locations.  They take the same arguments as memcpy() but will perform byte reversing as needed.  The example above could be re-written as:

    #include "endian.h"
    #include <stdio.h>
    
    int main() {
      uint8_t bytes[] = {0x11, 0x22, 0x33, 0x44};
      uint32_t v;
      
      MEMCPY_LE(&v, bytes, sizeof(uint32_t));
      printf("Interpreted as a little-endian byte stream, bytes = 0x%x\n", v);
      MEMCPY_BE(&v, bytes, sizeof(uint32_t));
      printf("Interpreted as a big-endian byte stream, bytes = 0x%x\n", v);
      return 0;
    }

## Unit Testing

`endian` includes built-in unit testing, which can be invoked as follows:

    $ cc -Wall -DUNIT_TEST -o endian endian.c
    $ ./endian
    Starting endian tests...
    ...finished endian tests

## Design

The read functions take a `void *src` pointer as an argument from which bytes are fetched.  Similarly, the
write functions take a `void *dst` pointer to specify where the converted data is to be stored.

Issues and pull requests are welcomed.
