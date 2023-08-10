#ifndef BIT_UTILS_H_
#define BIT_UTILS_H_

#include <cassert>

#include "other/type_alias.cpp"

namespace pll {

// ref: https://noshi91.github.io/Library/other/popcount.cpp
constexpr usize popcount(u64 x) {
#ifdef __GNUC__
    return __builtin_popcountll(x);
#else
    x -= x >> 1 & 0x5555555555555555;
    x = (x & 0x3333333333333333) + (x >> 2 & 0x3333333333333333);
    x = x + (x >> 4) & 0x0F0F0F0F0F0F0F0F;
    return x * 0x0101010101010101 >> 56 & 0x7f;
#endif
}

// return min {v | (x >> v) = 1}
// assert (msb(10) == 3); // 10 = 0b1010
//
// # Time
// do [msb(i) for i in range(1, 10 ** 8)] on AtCoder
// this version: 325ms, 324KB
// loop version: 1512ms, 296KB
constexpr usize get_msb(u32 x) {
    assert(x != 0);
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return popcount(x) - 1;
}
constexpr usize get_msb(u64 x) {
    assert(x != 0);
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    x |= (x >> 32);
    return popcount(x) - 1;
}

// return min {v | x <= (1 << v)}
// assert (smallest_pow2(10) == 16); // 8 < 10 < 16
constexpr u32 smallest_pow2(u32 x) {
    if (x <= 1) return 1;
    return 1 << (get_msb(x - 1) + 1);
}
constexpr u64 smallest_pow2(u64 x) {
    if (x <= 1) return 1;
    return 1 << (get_msb(x - 1) + 1);
}

}  // namespace pll

#endif
