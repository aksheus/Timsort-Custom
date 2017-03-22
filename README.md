# Timsort-Custom
A custom implementation of the timsort algorithm (not as good as the actual timsort !!) . It is an in-place sorting algorithm with bounded by O(nlogn) in wosrt case where n is number of items to be sorted

Requirements: 
sorts only integers 

Usage:
#include "timsort.h"
int_timsort(myArray,arrayLength)

Benchmark:
> python input_gen.py
> gcc interface.c -o interface
> interface < path to input.txt >
sorts one million integers in 0.163 seconds (cpu time)
