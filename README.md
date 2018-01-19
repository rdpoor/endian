# endian
endian is a collection of byte-order aware routines written in C for reading from and writing to arbitrary 
pointers in memory.

## Sample Usage

    #include "endian.h"
    #include <stdio.h>
    
    int main() {
      uint8_t bytes = {0x11, 0x22, 0x33, 0x44};
      printf("Interpreted as a little-endian byte stream, bytes = 0x%x\n", get_uint32_le((void *)bytes));
      printf("Interpreted as a big-endian byte stream, bytes = 0x%x\n", get_uint32_be((void *)bytes));
      return 0;
    }

## Unit Testing

`endian` includes built-in unit testing, which can be invoked as follows:

    $ cc -Wall -DUNIT_TEST -o endian endian.c
    $ ./endian
    Starting endian tests...
    ...finished endian tests

Note: If you want to extend the unit tests, take note of the comments about the `ENDIAN_ORDER` macro in `endian.c`.

## Design

The read functions take a `void *src` pointer as an argument from which bytes are fetched.  Similarly, the
write functions take a `void *dst` pointer to specify where the converted data is to be stored.  Compared 
to other byte-order libraries that take a byte-at-a-time read or write method, this approach allows endian
to shortcut conversion when the byte ordering of the host machine matches the desired byte ordering.

Issues and pull requests are welcomed.
