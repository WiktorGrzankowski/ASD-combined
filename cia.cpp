#include <bits/stdc++.h>

using namespace std;

int n, m;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    set<int> s;
    multiset<int> ms;
    map<int, int> before;
    map<int, int> after;
    cin >> n >> m;
    s.insert(0);
    s.insert(n);
    before[n] = 0;
    before[0] = -1;
    after[n] = -1;
    after[0] = n;
    ms.insert(n);
//    ms.insert(n);

    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        if (s.count(x) > 0) {
            cout << *ms.rbegin() << '\n';
            continue;
        }
        auto lbound = s.lower_bound(x);
        lbound--;
        auto rbound = s.upper_bound(x);
        int low = *lbound;
        int upp = *rbound;
        before[upp] = x;
        after[low] = x;
        before[x] = low;
        after[x] = upp;
        ms.erase(ms.lower_bound(upp - low));
        ms.insert(upp - x);
        ms.insert(x - low);
        s.insert(x);
        cout << *ms.rbegin() << '\n';
    }
}
