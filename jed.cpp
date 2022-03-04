#include <bits/stdc++.h>

using namespace std;
const int N_MAX = 500000;
uint n;
using LL = long long;
vector<int> v(N_MAX);

void calc(LL sum) {

}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cin >> n;


    LL far_bit = 0;
    LL bit_count = 0;
    for (uint i = 0; i < n; ++i) {
        LL x;
        cin >> x;
        if (v[x] == 1) {
            v[x] = 0;
            bit_count--;
            LL y = x + 1;
            while (v[y] == 1) {
                v[y] = 0;
                bit_count--;
                y++;
            }
            v[y] = 1;
            bit_count++;
            if (far_bit < y)
                far_bit = y;
        } else {
            v[x] = 1;
            bit_count++;
            if (x > far_bit)
                far_bit = x;
        }
        // obliczanie
        cout << bit_count << '\n';

    }
}
