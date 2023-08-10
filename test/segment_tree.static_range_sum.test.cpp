#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

// # Test for
// - segtree.swap
// - segtree.clear
// - segtree.empty
// - segtree.assign
// - segtree.resize
// - segtree.size

#include "ds/segment_tree.cpp"

#include <iostream>
#include <vector>

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    std::vector<int> a(n);
    for (auto& v : a) scanf("%d", &v);

    pll::segment_tree_t<pll::add_monoid_t<i64>> segtree(a.begin(), a.end());
    pll::segment_tree_t<pll::add_monoid_t<i64>> faketree(1);

    segtree.swap(faketree);
    segtree.swap(faketree);

    faketree.clear();
    assert(faketree.empty());

    faketree.assign(10, 1);
    assert(faketree.fold_all() == 10 and faketree.size() == 10);

    faketree.resize(5, 2);
    assert(faketree.fold_all() == 5 and faketree.size() == 5);

    faketree.resize(10, 2);
    assert(faketree.fold_all() == 15 and faketree.size() == 10);

    for (int i = 0; i < q; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);

        printf("%lld\n", segtree.fold(l, r));
    }
    return 0;
}
