#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int n, m;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cin >> n >> m;
    set<int> left;
    set<int> right;
    char sign;
    int l, r;
    int lmax, rmax;

    for (int i = 0; i < m; ++i) {
        cin >> sign >> l >> r;
        if (sign == '+') {
            if (l == 1) {
                left.insert(r);
            } else {
                right.insert(l);
            }
        } else {
            if (l == 1) {
                left.erase(r);
            } else {
                right.erase(l);
            }
        }
        // szukanie maxa
        if (left.empty())
            lmax = 0;
        else
            lmax = *left.rbegin(); // np 10 - 7, bo jest [1..7]
        if (right.empty())
            rmax = n + 1;
        else
            rmax = *right.begin(); // [2..10] to jest 1 element

        if (left.empty() && right.empty()) {
            cout << n << '\n';
            continue;
        }
        if (lmax + 1 >= rmax) {
            cout << 0 << '\n'; // są np [1..6] i [7..10]
        } else {
            // [1..2] i [99..100], ma wyjsc 100 - 2 - 2 = 96
            if (right.empty()) {
                cout << n - lmax << '\n';
            } else if (left.empty()) {
                cout << rmax - 1 << '\n';
            } else {
                // sa oba
                // 100 - 2 - (100 - 99 + 1) = 98 - 2 = 96
                cout << n - lmax - (n - rmax + 1) << '\n';
            }

        }
    }

    return 0;
}
