#include <bits/stdc++.h>

using namespace std;

typedef struct isle isle;

struct isle {
    pair<int, int> cords;
    int number;
};

// leksykograficznie
int compare_x(isle x, isle y) {
    return x.cords.first < y.cords.first;
}

int compare_y(isle x, isle y) {
    return x.cords.second < y.cords.second;
}


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

int count_distance(isle x, isle y) {
    return min(abs(x.cords.first - y.cords.first),
               abs(x.cords.second - y.cords.second));
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> wadj(n);
    vector<vector<isle>> neighbours(n); // zarowno ci po x jak i po y, max 4 rozne, obecnie moga sie powtarzac
    vector<isle> x_axis; // do posortowania po x
    vector<isle> y_axis; // do posortowania po y
    for (int i = 0; i < n; ++i) {
        isle new_isle;
        new_isle.number = i; /// NUMERUJEMY OD 0
        cin >> new_isle.cords.first >> new_isle.cords.second;
        x_axis.push_back(new_isle);
        y_axis.push_back(new_isle);
    }

    sort(x_axis.begin(), x_axis.end(), compare_x);
    sort(y_axis.begin(), y_axis.end(), compare_y);
    // posortowanie po x i po y
    // teraz nalezy utworzyc graf
    // gdzie waga to min (|a.x - b.x|, |a.y - b.y|)

    // tworzenie sasiadow

    // sasiedzi x-owi
    for (int i = 0; i < n - 1; ++i) {
        // 0 sasiaduje z 1, potem bedzie ze 1 sasiaduje z 2
        neighbours[x_axis[i].number].push_back(x_axis[i + 1]);
        neighbours[y_axis[i].number].push_back(y_axis[i + 1]);
        // 1 sasiaduje z 0, potem bedzie ze 2 sasiaduje z 1
        neighbours[x_axis[i + 1].number].push_back(x_axis[i]);
        neighbours[y_axis[i + 1].number].push_back(y_axis[i]);
    }

    /// elegancko
    // teraz utworzyc graf, tylko dla sasiadow, juz z odpowiednimi odleglosciami



    // tu bedzie wynik, interesuje nas ostatni wynik
    // bo idziemy zawsze od 0 i mamy po kolei koszt sciezki do 1, 2, ..., n - 1
//    vector<int> dist = dijkstra(wadj, 0);

    for (isle from : x_axis) {
        for (isle to : neighbours[from.number]) {
            wadj[from.number].push_back({to.number, count_distance(from, to)});
        }
    }
    vector<int> dist = dijkstra(wadj, 0);
    cout << dist[n - 1]; // sciezka od 0 do n - 1, czyli z tresci od 1 do n

    return 0;
}
