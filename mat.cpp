// Zadanie: Matryca
// Wiktor Grzankowski
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    string T;
    cin >> T;
    int l = 1000001;
    int n = T.size();
    char prevC = NULL;
    int prevJ = NULL;

    int resK = 1;

    for (int j = 0; j < n; ++j) {
        if (T[j] != '*') {
            if (prevC != NULL && T[j] != prevC) {
                l = min(l, j + 1 - prevJ);
            }
            prevC = T[j];
            prevJ = j;
        }
    }
    if (l != 1000001)
        resK = n + 1 - (l - 1);
    cout << resK;

    return 0;
}
