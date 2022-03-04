#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int s[n];
    for (int i = 0; i < n; ++i)
        cin >> s[i];

    int L[n][n];
    int R[n][n];

    // Najpierw obliczamy przekątne.
    for (int i = 0; i < n; ++i) {
        L[i][i] = 1;
        R[i][i] = 1;
    }

    // Teraz dla j - i == 1
    for (int i = 0; i < n - 1; ++i) {
        L[i][i + 1] = s[i] < s[i + 1];
        R[i][i + 1] = s[i] < s[i + 1];
    }
    

    for (int diff = 2; diff < n; ++diff) {
        for (int i = 0; i < n && i + diff < n; ++i) {
            int j = i + diff;
            L[i][j] = ((s[i] < s[i + 1]) * L[i + 1][j] + (s[i] < s[j]) * R[i + 1][j]) % 1000000000;
            R[i][j] = ((s[i] < s[j]) * L[i][j - 1] + (s[j - 1] < s[j]) * R[i][j - 1]) % 1000000000;
        }
    }

    cout << (L[0][n - 1] + R[0][n - 1] * (n > 1)) % 1000000000;

    return 0;
}
