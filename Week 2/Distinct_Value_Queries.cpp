#include <bits/stdc++.h>
using namespace std;

int n, q, blockSize;
vector<int> a, freq, res;
int distinct = 0;

struct Query {
    int l, r, idx;
    bool operator<(const Query &o) const {
        int blockA = l / blockSize, blockB = o.l / blockSize;
        return blockA != blockB ? blockA < blockB : r < o.r;
    }
};

void add(int x) {
    if (++freq[x] == 1) ++distinct;
}

void remove(int x) {
    if (--freq[x] == 0) --distinct;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    a.resize(n);
    vector<int> original(n);
    for (int i = 0; i < n; ++i) {
        cin >> original[i];
    }

    // Coordinate compression
    vector<int> vals = original;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(vals.begin(), vals.end(), original[i]) - vals.begin();
    }

    freq.assign(n, 0);
    res.resize(q);

    vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        queries[i] = {l - 1, r - 1, i}; // Convert to 0-based
    }

    blockSize = sqrt(n);
    sort(queries.begin(), queries.end());

    int l = 0, r = -1;
    for (auto& query : queries) {
        while (r < query.r) add(a[++r]);
        while (r > query.r) remove(a[r--]);
        while (l < query.l) remove(a[l++]);
        while (l > query.l) add(a[--l]);
        res[query.idx] = distinct;
    }

    for (int x : res) cout << x << '\n';
    return 0;
}
