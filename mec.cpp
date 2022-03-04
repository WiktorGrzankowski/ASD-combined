#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    // generujemy etykiety dla każdego zawodnika
    int n; // liczba zawodników, 4 <= n <= 40 000
    int m; // liczba meczów, 1 <= m <= 50
    cin >> n;
    cin >> m;
    bitset<50> E[n + 1];
    for (int i = 0; i < m; ++i) { // przechodzimy po m meczach
        for (int j = 0; j < n / 2; ++j) {
            int x;
            cin >> x;
            E[x][i] = true;
        }
        for (int j = n / 2; j < n; ++j) {
            int x;
            cin >> x;
            E[x][i] = false;
        }
    }

    // teraz tworzymy tablice ulongów
    unsigned long long Ell[n];
    for (int i = 1; i <= n; ++i) {
        Ell[i] = E[i].to_ullong();
    }

    // teraz sortujemy
    sort(Ell + 1, Ell + n + 1);

    bool result = true;
    for (int i = 2; i <= n; ++i) {
        if (Ell[i] == Ell[i - 1]) {
            result = false;
            break;
        }
    }
    if (result)
        cout << "TAK";
    else
        cout << "NIE";

    return 0;
}
