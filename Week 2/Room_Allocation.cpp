#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n;
    vector<tuple<int,int,int>> customers(n);

    for (int i = 0; i < n; i++) {
        int a, b; 
        cin >> a >> b;
        customers[i] = {a, b, i};
    }

    sort(customers.begin(), customers.end(), [](auto &x, auto &y) {
        return get<0>(x) < get<0>(y);
    });

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<int> room_of_customer(n);

    int room_count = 0;

    for (auto &[arrival, departure, idx] : customers) {
        if (!pq.empty() && pq.top().first < arrival) {
            auto [free_day, room] = pq.top();
            pq.pop();
            room_of_customer[idx] = room;
            pq.emplace(departure, room);
        } else {
            room_count++;
            room_of_customer[idx] = room_count;
            pq.emplace(departure, room_count);
        }
    }

    cout << room_count << "\n";
    for (int i = 0; i < n; i++) {
        cout << room_of_customer[i] << " ";
    }
    cout << "\n";

    return 0;
}
