// Zadanie: Bazarek
// Autor rozwiązania: Wiktor Grzankowski
#include <iostream>

//using namespace std;

int main() {
    std::ios_base::sync_with_stdio(0);
    int n;
    std::cin >> n; // liczba produktow
    int A[n]; // tablica produktow
    for (int i = 0; i < n; ++i) {
        std::cin >> A[i];
    }
    int m;
    std::cin >> m; // liczba dni u babci
    int K[m];
    for (int i = 0; i < m; ++i) { // liczba produktow do kupienia w kolejne dni
        std::cin >> K[i];
    }

    long long sum[n + 1]; // tablica sum ostatnich k elementów tablicy produktów
    sum[0] = 0;
    sum[1] = A[n - 1];
    for (int k = 2; k < n + 1; ++k) {
        sum[k] = sum[k - 1] + A[n - k];
    }

    int l0[n + 1]; // tablica najwiekszych parzystych elementow na lewo od k
    l0[n] = -1;
    int l1[n + 1]; // tablica najwiekszych nieparzystych elementow na lewo od k
    l1[n] = -1;

    for (int k = n - 1; k >= 0; --k) {
        if (A[n - k - 1] % 2 == 1) {
            l0[k] = l0[k + 1];
            l1[k] = A[n - k - 1];
        }
        else {
            l0[k] = A[n - k - 1];
            l1[k] = l1[k + 1];
        }
    }

    int r0[n + 1]; // tablica najmniejszych parzystych elementow na prawo od k wlacznie
    r0[0] = -1;
    int r1[n + 1]; // tablica najmniejszych nieparzystych elementow na prawo od k wlacznie
    r1[0] = -1;

    for (int k = 1; k < n + 1; ++k) {
        if (A[n - k] % 2 == 1) {
            r0[k] = r0[k - 1];
            r1[k] = A[n - k];
        }
        else {
            r0[k] = A[n - k];
            r1[k] = r1[k - 1];
        }
    }

    // wypisywanie m wierszy
    for (int i = 0; i < m; ++i) {
        long long res;
        if (sum[K[i]] % 2 == 1) {
            res = sum[K[i]];
        } else {
            res = -1;
            if (l1[K[i]] != -1 && r0[K[i]] != -1) {
                res = sum[K[i]] + l1[K[i]] - r0[K[i]];
            }
            if (l0[K[i]] != -1 && r1[K[i]] != -1) {
                res = std::max(res, sum[K[i]] + l0[K[i]] - r1[K[i]]);
            }
        }
        std::cout << res << std::endl;
    }

    return 0;
}
