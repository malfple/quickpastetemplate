// valid only for GCC compiler, used in bit operations

//clz - Returns the number of leading 0-bits in x, starting at the most significant bit position. If x is 0, the result is undefined.
int __builtin_clz (unsigned int x)
int __builtin_clzl (unsigned long)
int __builtin_clzll (unsigned long long)

//ctz - Returns the number of trailing 0-bits in x, starting at the least significant bit position. If x is 0, the result is undefined.
int __builtin_ctz (unsigned int x)
int __builtin_ctzl (unsigned long)
int __builtin_ctzll (unsigned long long)

//popcount - Returns the number of 1-bits in x.
int __builtin_popcount (unsigned int x)
int __builtin_popcountl (unsigned long)
int __builtin_popcountll (unsigned long long)