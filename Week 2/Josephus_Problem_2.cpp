#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size, 0);
    }

    void build(int n) {
        for (int i = 0; i < n; i++) {
            tree[size + i] = 1;
        }
        for (int i = size - 1; i > 0; i--) {
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }

    void update(int pos) {
        pos += size - 1;
        tree[pos] = 0;
        for (pos /= 2; pos > 0; pos /= 2) {
            tree[pos] = tree[2 * pos] + tree[2 * pos + 1];
        }
    }

    int query(int k) {
        int pos = 1;
        while (pos < size) {
            if (tree[2 * pos] >= k)
                pos = 2 * pos;
            else {
                k -= tree[2 * pos];
                pos = 2 * pos + 1;
            }
        }
        return pos - size + 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;

    SegmentTree seg;
    seg.init(n);
    seg.build(n);

    int current_pos = 0;  // zero-based position before any removal

    for (int i = 0; i < n; i++) {
        int alive = seg.tree[1];
        current_pos = (current_pos + k) % alive; 
        int pos_to_remove = current_pos + 1; // convert zero-based to 1-based

        int kid = seg.query(pos_to_remove);
        cout << kid << (i == n - 1 ? '\n' : ' ');
        seg.update(kid);
    }

    return 0;
}
