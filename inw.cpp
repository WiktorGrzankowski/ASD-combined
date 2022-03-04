#include <bits/stdc++.h>

using namespace std;

#define N_MAX 1e6
int n;
vector<int> input(N_MAX);
stack<int> representatives;
vector<vector<int>> graph(N_MAX);
vector<bool> visited(N_MAX, false);
vector<vector<int>> buckets(N_MAX);

void add_edge(int a, int b) {
    graph[a].push_back(b);
    graph[b].push_back(
            a);
}

// returns new biggest representative
void search_stack(int y) {
    int x;
    int maxx = -1;
    while (!representatives.empty()) {
        x = representatives.top();
        if (maxx == -1)
            maxx = x;

        if (x < y)
            break;

        representatives.pop();
        add_edge(x, y);
    }
    if (y > maxx) // nic nie wstawiono
        representatives.push(y);
    else
        representatives.push(maxx);
}

void dfs(int v) {
    visited[v] = true;
    for (int nei : graph[v]) {
        if (!visited[nei]) {
            dfs(nei);
        }
//        buckets
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> input[i];
    }
    for (int i = 1; i <= n; ++i) {
        search_stack(input[i]);
    }
    int curr_max = -1;
    int j = 0;
    cout << representatives.size() << '\n';
    for (int i = 1; i <= n; ++i) {
        curr_max = max(curr_max, input[i]);
        if (i == curr_max) {
            cout << i - j;
            for (int k = j + 1; k <= i; ++k) {
                cout << " " << k;
            }
            cout << '\n';
            j = i;
        }
    }




    return 0;
}
