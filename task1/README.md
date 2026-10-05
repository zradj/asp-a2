# Task 1 - Big vs. Little Endianness

## Overview of Endianness

When we work with numbers (specifically, integers) in high-level languages, we rarely think about how these numbers are stored in memory or transmitted via networks. We just see the number and take it for granted. However, at a low, hardware level, things become complicated.

If you worked in languages like Java or Rust, you know that there are 16-bit, 32-bit, 64-bit, and a few other types of integers. These numbers indicate how much memory it takes to represent each of these types of integers (and, consequently, how big of a number range a type supports). However, on the hardware level, all data is split into 8-bit (or 1 byte) chunks, including integers. This is where we face a choice on how to represent our numbers.

Let's say we have a 32-bit (4-byte) integer 1337133713. In binary notation, it looks like this:

```
01001111 10110011 00001010 10010001
   MSB                       LSB
```

Here, the Most Significant Byte (MSB) is `01001111`, because it represents the biggest part of the number: `(2^31 * 0 + 2^30 * 1 + 2^29 * 0 + 2^28 * 0 + 2^27 * 1 + 2^26 * 1 + 2^25 * 1 + 2^24 * 1) = 1325400064`. The Least Significant Byte (LSB), on the other hand, is `10010001`, because it represents the smallest part of the number: `(2^7 * 1 + 2^6 * 0 + 2^5 * 0 + 2^4 * 1 + 2^3 * 0 + 2^2 * 0 + 2^1 * 0 + 2^0 * 1) = 145`. For convenience reasons, let's use the hexadecimal notation from now on (it represents each four binary digits as one character):

```
4F B3 0A 91
```

The MSB is thus `4F` and the LSB is `91`.

There are two options on how to represent this number at a low level. The first one is called **Big Endian**:

```
Byte:       4F   B3   0A   91

Mem. addr:  0    1    2    3
```

Here, the MSB is stored at the lowest memory address and the LSB is stored at the highest.

The other option is called **Little Endian**:

```
Byte:       91   0A   B3   4F

Mem. addr:  0    1    2    3
```

Little Endian is the opposite of Big Endian: the LSB is stored at the lowest memory address and the MSB is stored at the highest.

## Usage and Endianness Bug Example

All in all, the initial choice on which endianness should be implemented is mostly arbitrary. If you somehow manage to create your own RAM or processor tomorrow, you may choose either one of them. Little Endian allows zero-cost type casting (for example, converting a 32-bit integer to an 8-bit one is trivial because the necessary bytes are already at the lowest address), while Big Endian is more intuitive and makes comparisons and sign testing easier (the sign bit and the most significant parts of the number are at the lowest address). Little Endian is commonly used in CPUs, Operating Systems, and microcontrollers. Big Endian, on the other hand, is commonly used in network protocols, file formats like JPEG or PNG, and legacy systems.

However, it is extremely important to be mindful of endianness in _existing_ systems, because different systems may implement different byte orderings. For instance, if you work with a low-level language like C and try to store a number in a variable straight from a network packet, you will most likely find out that the variable now contains some kind of garbage. This is because the network packet contains numbers in Big Endian, whereas variables are stored in Little Endian. This means that when you directly assign the network number to a variable, it reads a completely different number than intended. To fix this, you will have to explicitly convert Big Endian to Little Endian by performing a byte swap. Example for an unsigned 32-bit integer in C:

```c
#include <stdint.h>

uint32_t swap_uint32(uint32_t val) {
    return ((val >> 24) & 0x000000FF) |
           ((val >>  8) & 0x0000FF00) |
           ((val <<  8) & 0x00FF0000) |
           ((val << 24) & 0xFF000000);
}
```
