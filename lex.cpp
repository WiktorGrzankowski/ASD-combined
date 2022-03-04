#include <bits/stdc++.h>

using namespace std;

const int N = 300'000;
int n, m;
int from1, to1, from2, to2;
char s[N];

long long p = 31; // moze inne
long long q = 1e9 + 2137; // moze tez inne, pewnie większe

long long hashh(vector<long long> &powers ,vector<long long> &h,
                long long i, long long j) {
    long long res = (h[i] - ((h[j + 1] * powers[j - i + 1]) % q) + q) % q;
    return res;
}

string query(vector<long long> &powers, vector<long long> &h) {
    long long hash1, hash2;
    hash1 = hashh(powers, h, from1, to1);
    hash2 = hashh(powers, h, from2, to2);
    // binsearchem najdluzszy wspolny prefiks, hash rowny = podslowo rowne
    // mamy slowa s[from1..to1] i s[from2..to2]


    int r = min(to1 - from1, to2 - from2) + 1;
    int l = 0;
    while (l < r) {
        int mid = (l + r) / 2;
        if (hashh(powers, h, from1, from1 + mid) ==
            hashh(powers, h, from2, from2 + mid))
            l = mid + 1; // roznia sie gdzies dalej
        else
            r = mid; // roznia sie gdzies wczesniej
    }

    if (to1 - from1 == to2 - from2 && l == to1 - from1 + 1)
        return "=\n";
    if (to1 - from1 < to2 - from2 && l == min(to1 - from1, to2 - from2) + 1)
        return "<\n";
    if (to1 - from1 > to2 - from2 && l == min(to1 - from1, to2 - from2) + 1)
        return ">\n";
    if (s[from1 + l] < s[from2 + l])
        return "<\n";
    if (s[from1 + l] > s[from2 + l])
        return ">\n";
    // to nigdy nie powinno
    return "=\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    vector<long long> h(n + 1);
    vector<long long> powers(n + 1);
    powers[0] = 1;
    for (int r = 1; r <= n; ++r) {
        powers[r] = (powers[r - 1] * p) % q;
    }

    h[n] = 0; // s_n
    for (int i = n - 1; i >= 0; --i) {
        h[i] = (s[i] + h[i + 1] * p) % q; // od 0 do n - 1
    }
    // hasz dowolnego podslowa s[i..j] w czasie O(1), bo mamy wyliczone
    // w tablicy p^r mod q dla 0 <= r <= n
    // hash(s[i..j]) = (h[i] - h[j+1]*p^{j-i+1}) mod q

    for (int i = 0; i < m; ++i) {
        cin >> from1 >> to1 >> from2 >> to2;
        from1--;to1--;from2--;to2--;
        cout << query(powers, h);
    }
}
