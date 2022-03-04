#include <iostream>
#include <vector>

using namespace std;

struct T {
    int base;
    int size;
    vector<pair<char, int>> arr;


    void init() {
        for (int i = 1; i < size; ++i) {
            arr.push_back({'C', 0});
        }
    }

    pair<int, int> interval(int v) {
        int l = v;
        int r = v;
        while (l < base) {
            l = 2 * l;
            r = 2 * r + 1;
        }
        return {l, r};
    }

    void pushDown(int v) {
        int l = 2 * v;
        int r = 2 * v + 1;
        arr[l].first = arr[v].first;
        arr[r].first = arr[v].first;
        arr[l].second = arr[v].second / 2;
        arr[r].second = arr[v].second / 2;
    }

    void update(int v, int a, int b, char c) {
        pair<int, int> range = interval(v);
        int l = range.first, r = range.second;
        if (l - base + 1 > b || r - base + 1 < a) // iloczyn jest pusty
            return;
        if (l - base + 1 >= a && r - base + 1 <= b) {
            arr[v].first = c;
            arr[v].second = (c == 'B' ? r + 1 - l : 0);
        } else {
            if (arr[v].first == 'B' || arr[v].first == 'C')
                pushDown(v);
            update(2 * v, a, b, c);
            update(2 * v + 1, a, b, c);
            arr[v].first = (arr[2 * v].first == arr[2 * v + 1].first ? arr[2 *
                                                                           v].first
                                                                     : 'M');
            arr[v].second = arr[2 * v].second + arr[2 * v + 1].second;
        }
    }

    void printWhiteStripesCount() {
        cout << arr[1].second << '\n';
    }
};

int nearestPow2(int v) {
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n; // długość autostrady
    int m; // liczba dni i nocy
    cin >> n >> m;
    T tree;
    int base = nearestPow2(n);
    tree.base = base;
    tree.size = tree.base * 2;
//    tree->createArray();
    tree.init();
    // teraz kolejne kolorowania
    for (int i = 0; i < m; ++i) {
        int a, b;
        char colour;
        cin >> a >> b >> colour;
        tree.update(1, a, b, colour);
        tree.printWhiteStripesCount();
    }
    return 0;
}
