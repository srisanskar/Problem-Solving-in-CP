#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> p(n + 1);
        vector<int> child_count(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            cin >> p[i];
            if (p[i] != i) {
                child_count[p[i]]++;
            }
        }

        vector<bool> visited(n + 1, false);
        vector<vector<int>> paths;

        for (int i = 1; i <= n; i++) {
            // leaf node = no children
            if (child_count[i] == 0 && !visited[i]) {
                vector<int> path;
                int cur = i;
                while (!visited[cur]) {
                    path.push_back(cur);
                    visited[cur] = true;
                    if (p[cur] == cur) break; // root reached
                    cur = p[cur];
                }
                reverse(path.begin(), path.end());
                paths.push_back(path);
            }
        }

        cout << (int)paths.size() << "\n";
        for (auto &path : paths) {
            cout << (int)path.size() << "\n";
            for (int v : path) cout << v << " ";
            cout << "\n";
        }
    }

    return 0;
}
