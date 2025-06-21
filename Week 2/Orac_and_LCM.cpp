#include <bits/stdc++.h>
using namespace std;

const int MAX_A = 200000;
int spf[MAX_A + 1];

void sieve() {
    for (int i = 2; i <= MAX_A; i++) spf[i] = 0;
    for (int i = 2; i * i <= MAX_A; i++) {
        if (spf[i] == 0) {
            for (int j = i * i; j <= MAX_A; j += i) {
                if (spf[j] == 0) spf[j] = i;
            }
        }
    }
    for (int i = 2; i <= MAX_A; i++) {
        if (spf[i] == 0) spf[i] = i;
    }
}

vector<pair<int,int>> factorize(int x) {
    vector<pair<int,int>> factors;
    while (x > 1) {
        int p = spf[x], cnt = 0;
        while (x % p == 0) {
            x /= p;
            cnt++;
        }
        factors.emplace_back(p, cnt);
    }
    return factors;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();

    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    // For each prime p: 
    // count how many numbers do NOT have p
    // and track two smallest exponents among numbers that have p
    vector<int> zero_count(MAX_A + 1, n);
    vector<int> min1(MAX_A + 1, INT_MAX);
    vector<int> min2(MAX_A + 1, INT_MAX);

    for (int x : a) {
        auto f = factorize(x);
        vector<bool> seen_prime(MAX_A + 1, false);
        for (auto &[p, e] : f) {
            zero_count[p]--;
            if (e < min1[p]) {
                min2[p] = min1[p];
                min1[p] = e;
            } else if (e < min2[p]) {
                min2[p] = e;
            }
            seen_prime[p] = true;
        }
    }

    long long ans = 1;
    const long long LIMIT = 1e18;

    for (int p = 2; p <= MAX_A; p++) {
        if (zero_count[p] == n) continue; // prime doesn't appear at all

        int exponent = 0;
        if (zero_count[p] >= 2) {
            exponent = 0;
        } else if (zero_count[p] == 1) {
            exponent = min1[p];
        } else {
            exponent = min2[p];
        }
        for (int i = 0; i < exponent; i++) {
            ans *= p;
            if (ans > LIMIT) break;
        }
    }

    cout << ans << "\n";

    return 0;
}
