# Task 2 - `__sizeof__` behavior in Python

In this task, I will try to explain the following code and its output:

```python
tpl = (1, 2, 3)
print("tpl:", tpl.__sizeof__())

lst = [1, 2, 3]
print("lst:", lst.__sizeof__())
```

Output:

```
tpl: 56
lst: 72
```

## What `__sizeof__` does

The `__sizeof__` dunder method returns the size of a Python object in bytes. Only the memory consumption directly attributed to the object is accounted for, not the memory consumption of objects it refers to. The `sys.getsizeof()` is more recommended because it also accounts for the garbage collector's overhead if it manages the data structure. `__sizeof__()`, on the other hand, does not include the overhead. Source: [Python docs][1]

## Why these values?

The default sizes for different objects are not listed in the official documentation, because they heavily depend on the specific implementation used by a user. In this report, the following implementation was used:

```
C Implementation: CPython
Python Version: 3.14.7
Compiler: GCC 16.1.1 20260728
Operating System: linux
CPU Architecture: 64-bit
```

Since there are no official sizes, I had to experiment with different sizes of lists and tuples to understand the memory allocation behavior. Lists are explored first for better flow of arguments.

### Lists

I decided to see what happens if I create an empty list, a list with one element, two elements, three elements (our current case), four elements, five elements, and ten elements:

```python
lst = []
print("lst (0):", lst.__sizeof__())
lst = [1]
print("lst (1):", lst.__sizeof__())
lst = [1, 2]
print("lst (2):", lst.__sizeof__())
lst = [1, 2, 3]
print("lst (3):", lst.__sizeof__())
lst = [1, 2, 3, 4]
print("lst (4):", lst.__sizeof__())
lst = [1, 2, 3, 4, 5]
print("lst (5):", lst.__sizeof__())
lst = list(range(10))
print("lst (10):", lst.__sizeof__())
```

Outputs:

```
lst (0): 40
lst (1): 48
lst (2): 56
lst (3): 72
lst (4): 72
lst (5): 88
lst (10): 120
```

First, we see that 40 bytes is the list overhead because an empty list has this size. These 40 bytes are probably a C struct that contains the meta information about the list. After that, we can observe that Python allocates 8 bytes (the size of an integer) per element for lists that contain one and two elements. However, for the three-element list, Python preemptively allocates space for four elements. I went further and sampled 10 random list sizes from 0 to 100 to investigate the allocation behavior closer:

```python
import random

for i in random.sample(range(101), 10):
    lst = list(range(i))
    print(f"lst ({i}):", lst.__sizeof__(), "; alloc for:", (lst.__sizeof__() - 40) / 8)
```

Output:

```
lst (59): 520 ; alloc for: 60.0
lst (2): 56 ; alloc for: 2.0
lst (100): 840 ; alloc for: 100.0
lst (91): 776 ; alloc for: 92.0
lst (74): 632 ; alloc for: 74.0
lst (84): 712 ; alloc for: 84.0
lst (21): 216 ; alloc for: 22.0
lst (43): 392 ; alloc for: 44.0
lst (38): 344 ; alloc for: 38.0
lst (27): 264 ; alloc for: 28.0
```

It appears that Python allocates space for one extra element when the list has an odd number of elements (except for 1). When it has an even number of elements, the allocation matches this number. The reason for this behavior is described in [CPython's source code][2]:

```c
/* Since the Python memory allocator has granularity of 16 bytes on 64-bit
 * platforms (8 on 32-bit), there is no benefit of allocating space for
 * the odd number of items, and there is no drawback of rounding the
 * allocated size up to the nearest even number.
 */
size = (size + 1) & ~(size_t)1;
```

### Tuples

Empty tuple size:

```python
tpl = tuple()
print(tpl.__sizeof__())
```

Output:

```
32
```

For tuples, I decided to immediately apply the random sampling described in the previous section:

```python
import random

for i in random.sample(range(101), 10):
    tpl = tuple(range(i))
    print(f"tpl ({i}):", tpl.__sizeof__(), "; alloc for:", (tpl.__sizeof__() - 32) / 8)
```

Outputs:

```
tpl (48): 416 ; alloc for: 48.0
tpl (73): 616 ; alloc for: 73.0
tpl (80): 672 ; alloc for: 80.0
tpl (50): 432 ; alloc for: 50.0
tpl (26): 240 ; alloc for: 26.0
tpl (27): 248 ; alloc for: 27.0
tpl (21): 200 ; alloc for: 21.0
tpl (92): 768 ; alloc for: 92.0
tpl (58): 496 ; alloc for: 58.0
tpl (34): 304 ; alloc for: 34.0
```

From these outputs, it is clear that Python just adds 8 bytes per each element to the 32-byte empty tuple overhead. This makes sense because tuples are immutable, so there is no reason to ever allocate more memory than necessary. The granularity point from the previous section should also apply here in the C implementation, but it probably is not shown in `__sizeof__` because the extra size will never be used.

[1]: https://docs.python.org/3/library/sys.html#sys.getsizeof
[2]: https://github.com/python/cpython/blob/e0c28e2a00746e9100969868a71f0e5524450ded/Objects/listobject.c#L198-L203
