#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

// # Test for
// - segtree.update
// - segtree.fold
// - segtree.fold_all
// - segtree.set_need_build
// - segtree.build

#include "ds/segment_tree.cpp"

#include <iostream>
#include <vector>

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    std::vector<int> a(n);
    for (auto& v : a) scanf("%d", &v);

    pll::segment_tree_t<pll::add_monoid_t<i64>> segtree(n);
    for (int i = 0; i < n; ++i) segtree.set_need_build(i, a[i]);
    segtree.build();

    for (int i = 0; i < q; ++i) {
        int t, l, r;
        scanf("%d%d%d", &t, &l, &r);

        if (t == 0)
            segtree.update(l, r);
        else
            printf("%lld\n", segtree.fold(l, r));

        assert(segtree.fold(0, n) == segtree.fold_all());
    }
    return 0;
}
