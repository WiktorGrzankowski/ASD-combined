#include <bits/stdc++.h>

using namespace std;

int n, m;
int found = 0;

bool visited[500000];

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cin >> n >> m;
    vector<vector<pair<int, int>>> vec(n + 1);
    int u1, v1, w1;
    for (int i = 0; i < m; ++i) {
        cin >> u1 >> v1 >> w1;
        vec[u1].push_back({v1, w1});
        vec[v1].push_back({u1, w1});
    }

    int ind = 1;
    long long result = 0;
    while (ind < n) {
        if (visited[ind]) {
            ind++;
        } else {
            queue<int> q;
            q.push(ind);

            while (!q.empty()) {
                int v = q.front();
                visited[v] = true;
                q.pop();
                map<int, int> w;
                int size = 0;
                for (auto &u_pair : vec[v]) {
                    if (!visited[u_pair.first]) {
                        visited[u_pair.first] = true;
                        q.push(u_pair.first);
                    }
                    auto it = w.find(u_pair.second); // waga tej krawedzi
                    if (it != w.end() && !w.empty()) {
                        // powtórka
                        result += size - w[u_pair.second];
                        w[u_pair.second]++;
                    } else if (!w.empty()) {
                        // nowa wartosc
                        result += size;
                        w[u_pair.second] = 1;
                    } else {
                        // pusty w
                        w.insert({u_pair.second, 1});
                    }
                    size++;
                }
            }
        }
    }
    cout << result;

}
