#include <bits/stdc++.h>

using namespace std;

vector<bool> visited;
vector<vector<int>> g;

// Dodaje krawędzie do grafu nieskierowanego.
void edge(int a, int b) {
    g[a].push_back(b);
    g[b].push_back(a);
}

// Znajduje najkrótszą scieżkę w grafie przy użyciu algorytmu bfs.
vector<int> path(int curr, int end) {
    // visited juz ogarniete
    vector<int> previous(end + 1);
    vector<int> dist(end + 1);
    dist[curr] = 0;
    previous[curr] = -1;
    queue<int> q;
    q.push(curr);
    visited[curr] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : g[v]) {
            if (!visited[u]) {
                visited[u] = true;
                q.push(u);
                dist[u] = dist[v] + 1;
                previous[u] = v;
            }
        }
    }

    vector<int> path;
    int dest = end;
    if (!visited[dest]) {
        vector<int> brak;
        brak.push_back(-1);
        cout << -1; // Nie znaleziono sciezki.
        return brak;
    } else {
        int x = dest;
        while (x != -1) {
            path.push_back(x);
            x = previous[x];
        }
    }
    reverse(path.begin(), path.end());
    return path;
}

void printResult(vector<int> path, int maxLast, vector<int> whereCharge) {
    cout << path.size() << " " << maxLast << " " << whereCharge.size()
         << '\n';
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1)
            cout << " ";
    }
    cout << '\n';
    for (int i = whereCharge.size() - 1; i >= 0; --i) {
        cout << whereCharge[i];
        if (i > 0)
            cout << " ";
    }
}

void findOptimalCharching(vector<int> path, vector<int> whereCharge, int energy,
                          int cost, set<int> forbidden, vector<int> e) {
    // <bool, bool> -> <czy można uzyskać wartość, czy ta wartość jest efektem ładowania na tym skrzyżowaniu>
    pair<bool, bool> T[path.size()][energy + 1];
    for (int i = 0; i < energy; ++i) {
        T[0][i] = {false, false};
    }
    T[0][energy] = {true, false};
    for (int i = 1; i < path.size(); ++i) {
        for (int j = 0; j <= energy; ++j) {
            if (j + cost <= energy) { 
                T[i][j].first = T[i - 1][j + cost].first;
                T[i][j].second = false;
                if (j - e[i] >= 0 && T[i][j].first == false) { // Można sprawdzić, czy da się doładować do tej wartości.
                    if (T[i][j - e[i]].first && forbidden.count(j) == 0 &&
                        T[i][j - e[i]].second == false) { // Doładowanie nie doprowadzi do awarii.
                        T[i][j] = {true,true};
                    } else {
                        T[i][j] = {false, false};
                    }
                }
            } else { 
                if (j - e[i] >= 0) { // Można sprawdzić, czy da się doładować.
                    if (T[i][j - e[i]].first && forbidden.count(j) == 0 &&
                        T[i][j - e[i]].second == false) { // Doładowanie nie doprowadzi do awarii,
                        T[i][j] = {true,true};
                    } else {
                        T[i][j] = {false, false};
                    }
                } else {
                    T[i][j] = {false, false};
                }
            }
        }
    }
    
    // Znajdujemy największą wartość końcową i patrzymy jak ją uzyskaliśmy
    int maxLast = -1;
    for (int i = 0; i <= energy; ++i) {
        if (T[path.size() - 1][i].first == true) {
            maxLast = i;
        }
    }
    if (maxLast < 0) { // Nie można dojść do ostatniego skrzyżowania.
        cout << -1;
        return;
    }
    
    bool rootFound = false;
    int dist = path.size() - 1;
    int en = maxLast;
    while (!rootFound) {
        if (T[dist][en].second == true) { // Wartość jest efektem doładowania.
            whereCharge.push_back(path[dist]);
            en -= e.at(dist);
        } else {
            dist--; 
            en += cost;
        }
        if (dist == 0 && T[dist][en].second == false)
            rootFound = true;
    }

    printResult(path, maxLast, whereCharge);
}


// start: 1, end: n, energy: p, cost: k, forbidden: zw_1,...,zw_z, e: e_0,...,e_{n-1}
void bfs(int start, int end, int energy, int cost, set<int> forbidden,
         vector<int> e) {
    vector<int> shortest = path(start, end); // Najkrótsza scieżka od 1 do n.
    if (!(shortest.size() == 1 && shortest[0] == -1)) {
        vector<int> whereCharge; // Liczba ładowań to rozmiar wektora.
        findOptimalCharching(shortest, whereCharge, energy, cost, forbidden, e);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int p; // pojemność akumulatora, na początku akumulator jest pełen
    int k; // koszt przejechania odcinka drogi
    int z; // liczba zabronionych wartości
    cin >> p >> k >> z;
    set<int> forbidden; // zbiór zabronionych wartości
    for (int i = 0; i < z; ++i) {
        int zw;
        cin >> zw;
        forbidden.insert(zw);
    }
    int n; // liczba skrzyżowań
    int m; // liczba dróg
    cin >> n >> m;
    visited.assign(n + 1,false); // na początku nie odwiedziliśmy żadnego skrzyżowania
    g.assign(n + 1, vector<int>()); // inicjujemy graf
    for (int i = 0; i < m; ++i) { // m odcinków (a,b)
        int a;
        int b;
        cin >> a >> b;
        edge(a, b);
    }
    vector<int> e(n); // moce powerbanków na skrzyżowaniach oddalonych od początku o odległość równą indeksowi
    for (int i = 0; i < n; ++i) {
        int eHelp;
        cin >> eHelp;
        e[i] = eHelp;
    }
    bfs(1, n, p, k, forbidden, e);
    return 0;
}
