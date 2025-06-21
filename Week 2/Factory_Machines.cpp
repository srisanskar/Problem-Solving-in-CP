#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long t;
    cin >> n >> t;
    vector<long long> k(n);
    for (int i = 0; i < n; i++) cin >> k[i];

    long long left = 0, right = 1e18;
    while (left < right) {
        long long mid = left + (right - left) / 2;
        long long products = 0;
        for (int i = 0; i < n; i++) {
            products += mid / k[i];
            if (products >= t) break;
        }
        if (products >= t)
            right = mid;
        else
            left = mid + 1;
    }
    cout << left << "\n";
    return 0;
}
