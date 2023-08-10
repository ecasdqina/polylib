#ifndef SEGMENT_TREE_H_
#define SEGMENT_TREE_H_

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

#include "ds/monoid.cpp"
#include "other/bit_util.cpp"

namespace pll {

template <class Monoid>
class segment_tree_t {
   public:
    using value_type = typename Monoid::value_type;

   private:
    usize n;
    usize base;  // = min {v | n <= (1 << v)}
    std::vector<value_type> a;

    // when node x holds [l, r) return r
    usize get_right_index(usize x) const {
        const usize msb = get_msb(x);
        return std::min(n, (base >> msb) * (x & ((1 << msb) - 1) + 1));
    }
    // when node x holds [l, r) return l
    usize calc_left_index(usize x) const {
        const usize msb = get_msb(x);
        return (base >> msb) * (x & ((1 << msb) - 1));
    }

   public:
    segment_tree_t() : n(0), base(0), a(0) {}
    segment_tree_t(usize n) : n(n), base(smallest_pow2(n)) {
        a.assign(base << 1, Monoid::identity());
    }
    segment_tree_t(usize n, const value_type &v) : segment_tree_t(n) {
        std::fill(a.begin() + base, a.begin() + base + n, v);
        build();
    }
    template <class InputIt>
    segment_tree_t(InputIt first, InputIt last)
        : segment_tree_t(std::distance(first, last)) {
        for (usize i = 0; first != last; ++first, ++i) a[i + base] = *first;
        build();
    }

    // overall change functions
    void build() {
        for (usize i = base - 1; i > 0; --i) {
            a[i] = Monoid::operation(a[2 * i + 0], a[2 * i + 1]);
        }
    }

    void assign(usize n, const value_type &x) { *this = segment_tree_t(n, x); }
    void resize(usize n, const value_type &x = Monoid::identity()) {
        auto nseg = segment_tree_t(n, x);
        for (usize i = 0; i < std::min(n, size()); ++i)
            nseg.set_need_build(i, a[base + i]);
        nseg.build();
        *this = nseg;
    }
    void clear() {
        n = base = 0;
        a.clear();
    }
    void swap(segment_tree_t &b) {
        std::swap(n, b.n);
        std::swap(base, b.base);
        a.swap(b.a);
    }

    // update functions
    void set_need_build(usize k, const value_type &v) { a[k + base] = v; }
    void change(usize k, const value_type &v) {
        k += base;
        a[k] = v;
        while (k >>= 1) {
            a[k] = Monoid::operation(a[2 * k + 0], a[2 * k + 1]);
        }
    }
    void update(usize k, const value_type &v) {
        change(k, Monoid::operation(a[k + base], v));
    }

    // fold functions
    const value_type &fold_all() const { return a[1]; }
    value_type fold(usize first, usize last) const {
        if (last <= first) return Monoid::identity();

        first += base;
        last += base;

        value_type lval = Monoid::identity();
        value_type rval = Monoid::identity();
        while (first != last) {
            if (first & 1) lval = Monoid::operation(lval, a[first++]);
            if (last & 1) rval = Monoid::operation(a[--last], rval);

            first >>= 1;
            last >>= 1;
        }
        return Monoid::operation(lval, rval);
    }

    const value_type &operator[](const usize &k) const { return a[k + base]; }

    usize size() const { return n; }
    bool empty() const { return n == 0; }
};

}  // namespace pll

#endif
