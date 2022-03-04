#include <bits/stdc++.h>

using namespace std;
#define N_MAX 200000
#define M_MAX 500000
int n, m;
vector<vector<int>> g(N_MAX + 1);
vector<bool> visited(N_MAX + 1);

struct Node{
    int v, parent;
};

bool bfs(int src) {
    visited[src] = true;
    queue<Node> q;
    q.push({src, -1});
    while (!q.empty()) {
        Node node = q.front();
        q.pop();

        for (int u : g[node.v]) {
            if (!visited[u]) {
                visited[u] = true;
                q.push({u, node.v});
            } else if (u != node.parent) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cin >> n >> m;

    int e1, e2;
    for (int i = 0; i < m; ++i) {
        cin >> e1 >> e2;
        g[e1].push_back(e2);
        g[e2].push_back(e1);
    }
    bool res = false;
    for (int v = 1; v < n + 1; ++v) {
        if (res)
            break;
        if (!visited[v]) {
            res = bfs(v);
        }
    }
    if (res)
        cout << "TAK";
    else
        cout << "NIE";
}
