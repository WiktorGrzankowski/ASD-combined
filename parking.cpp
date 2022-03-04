#include <bits/stdc++.h>

using namespace std;
const int N_MAX = 1e5 * 5;
vector<vector<int>> g(N_MAX);
//vector<bool> visited(N_MAX, false);
vector<int> parked(N_MAX);
vector<bool> success(N_MAX);

vector<int> dijkstra(const vector<vector<pair<int, int>>> &wadj, int source) {
    int n = (int) wadj.size();
    vector<int> dist(n);
    vector<bool> visited(n, false);
    // poczatkowo wszedzie int_max oprocz sciezki do samego siebie
    for (int i = 0; i < n; i++)
        dist[i] = (i == source ? 0 : INT_MAX);
    // <priorytet, wierzcholek>
    priority_queue<pair<int, int>, vector<pair<int, int>>,
            greater<pair<int, int>>> q;
    q.push({dist[source], source});
    while (!q.empty()) {
        auto[d, v] = q.top();
        q.pop();
        if (visited[v])
            continue;
        assert(d == dist[v]);
        visited[v] = true;
        for (const auto &[u, edge_w] : wadj[v]) { // tablica sasiadow
            // najpierw do v biorac odleglosc d
            // plus przejscie do u
            if (d + edge_w < dist[u]) {
                dist[u] = d + edge_w;
                q.push({dist[u], u});
            }

        }
    }
    return dist; // odleglosci do wszystkiego ze wszystkiego
}

int count_weight(int v, int u) {
    if (parked[u] || parked[v])
        return 1;

    return 0;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i < n + 1; ++i) {
        int x;
        cin >> x;
        parked[i] = x;
        success[i] = false;
    }
    int v1, v2;
    for (int i = 0; i < m; ++i) {
        cin >> v1 >> v2;
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }
    vector<vector<pair<int, int>>> wadj(n + 1);
    for (int v = 1; v < n + 1; ++v) {
        for (int u : g[v]) {
            wadj[v].push_back({u, count_weight(v, u)});
        }
    }
    vector<int> dist = dijkstra(wadj, 1);
    for (int v = 1; v < n + 1; ++v) {
        if (parked[v] && dist[v] == 1)
            cout << v << '\n';
    }
//    cout <<"a";
}
