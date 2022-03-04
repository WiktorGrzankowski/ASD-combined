#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> v;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        v.push_back(x);
    }
    sort(v.begin(), v.end());
    int curr_len = 1;
    int m_len = -1;
    for (int i = 1; i < n; ++i) {
        if (v.at(i) - v.at(i - 1) <= 1) {
            curr_len++;
        } else {
            if (curr_len > m_len)
                m_len = curr_len;
            curr_len = 1;
        }
    }
    if (curr_len > m_len)
        m_len = curr_len;
    cout << m_len;



}
