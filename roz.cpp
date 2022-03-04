#include <bits/stdc++.h>

using namespace std;
int n, d;
vector<int> v;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cin >> n >> d;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        v.push_back(x);
    }
    sort(v.begin(), v.end());
    int i = 0, j = 0;

    while (j < n && i < n) {
        if (v[j] - v[i] == d && i != j) {
            cout << v[j] << " " << v[i];
            return 0;
        } else if (v[j] - v[i] < d) {
            j++;
        } else {
            i++;
        }
    }
    cout << "NIE";
}
