#include <bits/stdc++.h>

using namespace std;
int n, m;
int e1, e2;

bool contains_odd(int src, vector<vector<int>> &g, vector<bool> &visited,
                  int colorArr[]) {
    colorArr[src] = 1;
    visited[src] = true;
    queue<int> q;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto &v : g[u]) {
            visited[v] = true;
            if (colorArr[v] == -1) {
                colorArr[v] = 1 - colorArr[u];
                q.push(v);
            } else if (colorArr[v] == colorArr[u]) {
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
    vector<vector<int>> g(n + 1);
    vector<bool> visited(n + 1);
    int colorArr[n + 1];
    for (int i = 1; i <= n; ++i) {
        colorArr[i] = -1;
    }
    for (int i = 0; i < m; ++i) {
        cin >> e1 >> e2;
        g[e1].push_back(e2);
        g[e2].push_back(e1);
    }
    bool res;
    res = contains_odd(1, g, visited, colorArr);
    for (int i = 1; i < n + 1; ++i) {
        if (res)
            break;
        if (!visited[i]) {
            res = contains_odd(i, g, visited, colorArr);
        }
    }
    if (res)
        cout << "NIE";
    else
        cout << "TAK";
}
