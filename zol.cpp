#include <bits/stdc++.h>

using namespace std;


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    cin >> n;
    set<int> s;
    for (int i = 1; i <= n; ++i) {
        s.insert(i);
    }
    int z;
    int lval, rval;
    for (int i = 0; i < n; ++i) {
        cin >> z;
        auto l = s.lower_bound(z);
        l--;
        auto r = s.upper_bound(z);
        if (l != s.end() & r != s.end()) {
            lval = *l;
            rval = *r;
            if (lval >= rval) {
                lval = -1;
                rval = -1;
            }
        } else if (l != s.end()) {
            lval = *l;
            if (lval >= z)
                lval = -1;
            rval = -1;
        } else if (r != s.end()) {
            rval = *r;
            lval = -1;
        } else {
            lval = -1;
            rval = -1;
        }
        if (lval == 0 || lval == z)
            lval = -1;
        if (lval == rval) {
            lval = -1;
            rval = -1;
        }
        s.erase(z);
        cout << lval << " " << rval << '\n';


    }
}
