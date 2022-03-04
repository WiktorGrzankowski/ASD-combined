#include <bits/stdc++.h>
using namespace std;

#define N 300001

int n, k;
int l, p;
int pairity = 0;
int target, rotations_left;

string T;

int rotations[N];
int rotations_range[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k >> T;

    for (int i = 0; i < k; i++) {
        cin >> l >> p;

        if (l == p) {
            continue;
        }

        rotations[l - 1] = (p - l + 1) / 2;
        rotations[p - 1]--;

        rotations_range[l - 1] = p - 1;

    }

    for (int i = 0; i < n; i++) {
        if (rotations_range[i]) {
            target = rotations_range[i];
        }

        if (rotations[i]) {
            rotations_left = rotations[i];
            rotations[i] > 0 ? pairity++ : pairity--;
        }

        if (pairity % 2 == 1 && target > i) {
            swap(T[i], T[target]);
        }

        // These can go negative - they will be overwritten eventually.
        rotations_left--;
        target--;
    }

    cout << T;

    return 0;
}

/*
9 4
abcdefghi
1 6
3 4
7 9
2 5
 */
