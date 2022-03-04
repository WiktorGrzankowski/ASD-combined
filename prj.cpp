#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <set>

using namespace std;

class Compare {
public:
    bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.second > b.second;
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);

    std::cin.tie(NULL);
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> howManyProgrammers(n);
    vector<int> dependencies(n);
    for (int i = 0; i < n; ++i) {
        cin >> howManyProgrammers[i];
        dependencies[i] = 0;
    }
    // teraz zaleznosci
    vector<vector<int>> dependent(n);
    // <1; 2, 3> np
    int tmp1, tmp2;
    for (int i = 0; i < m; ++i) {
        cin >> tmp1 >> tmp2;
        dependent[tmp2 - 1].push_back(tmp1 - 1);
        dependencies[tmp1 - 1]++;
    }
    // tablica zaleznosci jest dobrze
    priority_queue<pair<int, int>, vector<pair<int, int>>,
            Compare> q;

    for (int i = 0; i < n; ++i) {
        if (dependencies[i] == 0) {
            // nie zalezy od nikogo
            q.push({i, howManyProgrammers[i]});
        }
    }
    // tablica niezaleznych git
    int count = 0, max = 0;
    while (count < k) {
        pair<int, int> elem = q.top();
        q.pop();
        count++;
        if (elem.second > max)
            max = elem.second;

        for (int i : dependent[elem.first]) {
            // usuwamy wszystkie zaleznosci od tego, ktorego wzielismy z kolejki
            dependencies[i]--;
            if (dependencies[i] == 0)
                q.push({i, howManyProgrammers[i]});
        }

    }
    cout << max;


    return 0;
}