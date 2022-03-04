#include <iostream>
#include <vector>

using namespace std;

int n;
void findFarDown(int u, pair<int, int> farDown[],int left[], int right[]) {
    // post order
    if (left[u] != -1)
        findFarDown(left[u], farDown, left, right);
    if (right[u] != -1)
        findFarDown(right[u], farDown, left, right);
    pair<int, int> res;
    pair<int, int> c1 = {0, u};
    res = c1;
    pair<int, int> c2 = {0, u}, c3 = {0, u};
    if (left[u] != -1) {
        c2.first = farDown[left[u]].first + 1;
        c2.second = farDown[left[u]].second;
        if (c2.first > res.first)
            res = c2;
    }
    if (right[u] != -1) {
        c3.first = farDown[right[u]].first + 1;
        c3.second = farDown[right[u]].second;
        if (c3.first > res.first)
            res = c3;
    }
    farDown[u] = res;
    // fardown[u] = najlepszy z c1, c2, c3

}

void findfarUp(int u, pair<int, int> farDown[],int left[], int right[],
               pair<int, int> farUp[], int parent[], int sibling[]) {
    // pre order
    pair<int, int> res;
    pair<int, int> c1 = {0, u};
    pair<int, int> c2, c3;
    res = c1;
    if (parent[u] != -1) {
        c2.first = farUp[parent[u]].first + 1;
        c2.second = farUp[parent[u]].second;
        if (c2.first > res.first)
            res = c2;
    }
    if (sibling[u] != -1) {
        c3.first = farDown[sibling[u]].first + 2;
        c3.second = farDown[sibling[u]].second;
        if (c3.first > res.first)
            res = c3;
    }
    farUp[u] = res;
    if (left[u] != -1)
        findfarUp(left[u], farDown, left, right, farUp, parent, sibling);
    if (right[u] != -1)
        findfarUp(right[u], farDown, left, right, farUp, parent, sibling);
}

void findDepth(int depth[], int *currDepth, int index,
               int left[], int right[], int parent[]) {
    (*currDepth)++;
    depth[index] = *currDepth;
    if (left[index] != -1) {
        parent[left[index]] = index;
        findDepth(depth, currDepth, left[index], left, right, parent);
    }
    if (right[index] != -1) {
        parent[right[index]] = index;
        findDepth(depth, currDepth, right[index], left, right, parent);
    }
    (*currDepth)--;
}

int floorLog2(int x) {
    int tempn = x;
    int log2n = 0;
    while (tempn >>= 1)
        ++log2n;
    return log2n;
}

// zwraca wierzchołek oddalony od v o odległość h
int ancestor(int v, int h, vector<vector<int>> &links) {
    int res = v;
    int i = floorLog2(n);
    while (h > 0) {
        if ((1 << i) > h) {
            --i;
        } else {
            res = links[i][res];
            h -= 1 << i;
        }
    }
    return res;
}

int lca(int u, int v, int depth[],
        vector<vector<int>> &links, int parent[]) {
    int depth_u = depth[u];
    int depth_v = depth[v];
    if (depth_u < depth_v) { // v jest głębiej
        v = ancestor(v,depth_v - depth_u, links);
//        depth_v = depth[v]; // nowa glebokosc
    } else if (depth_u > depth_v) {
        u = ancestor(u, depth_u - depth_v, links);
//        depth_u = depth[u];
    }
    if (u == v)
        return u;
    int i = floorLog2(n);
    while (i >= 0) {
        if (links[i][u] != links[i][v]) {
            u = links[i][u];
            v = links[i][v];
        }
        i--;
    }

    return parent[u];
}

int dist(int u, int d, int depth[], pair<int, int> far[],
         vector<vector<int>> &links, int parent[]) {
    pair<int, int> max_v = far[u];
    if (d > max_v.first)
        return -1;
    int u_v_lca = lca(u, max_v.second, depth, links, parent);
    int d1 = depth[u] - depth[u_v_lca];
//    int d2 = depth[max_v.second] - depth[u_v_lca];
    if (d <= d1)
        return ancestor(u, d, links);
    int res = ancestor(max_v.second, max_v.first - d, links);
    return res/*ancestor(max_v.second, max_v.first - d, n, links)*/;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cin >> n; // liczba polanek
    int parent[n + 1], left[n + 1], right[n + 1];
    int sibling[n + 1];
    sibling[1] = -1;
    for (int i = 1; i < n + 1; ++i) { // kolejne scieżki lub ich brak
        parent[i] = -1; // potem uzupelnimy rodzicow
        cin >> left[i];
        cin >> right[i];
        if (left[i] != -1 && right[i] != -1) {
            sibling[left[i]] = right[i];
            sibling[right[i]] = left[i];
        } else {
            sibling[left[i]] = -1;
            sibling[right[i]] = -1;
        }
    }
    int m;
    cin >> m; // liczba pytań Bajtyny
    pair<int, int> questions[m];
    for (int i = 0; i < m; ++i) {
        cin >> questions[i].first >> questions[i].second;
    }
    // teraz obliczyc depth
    int depth[n + 1];
    depth[1] = 0;
    int currDepth = 0;
    if (left[1] != -1) {
        parent[left[1]] = 1;
        findDepth(depth, &currDepth, left[1], left, right, parent);
    }
    if (right[1] != -1) {
        parent[right[1]] = 1;
        findDepth(depth, &currDepth, right[1], left, right, parent);
    }

    int log2n = floorLog2(n);

    vector<vector<int>> links(log2n + 1, vector<int> (n + 1));


    for (int v = 1; v < n + 1; ++v) {
        links[0][v] = parent[v];
    }
    for (int i = 1; i < log2n + 1; ++i) { // links działa gitara
        for (int v = 1; v < n + 1; ++v) {
            if (links[i - 1][v] == -1)
                links[i][v] = -1;
            else
                links[i][v] = links[i - 1][links[i - 1][v]];
        }
    }

    
    pair<int, int> farDown[n + 1];
    findFarDown(1, farDown, left, right);

    pair<int, int> farUp[n + 1];
    findfarUp(1, farDown, left, right, farUp, parent, sibling);
    pair<int, int> far[n + 1];
    for (int i = 1; i < n + 1; ++i) {
        if (farUp[i].first > farDown[i].first)
            far[i] = farUp[i];
        else
            far[i] = farDown[i];
//        cout << "far[" << i<<"] = " << far[i].first << ", " << far[i].second << "\n";
    }

    // far znalezione poprawnie
    for (int i = 0; i < m; ++i) {
        cout << dist(questions[i].first, questions[i].second, depth,
                     far, links, parent) << '\n';
    }
    return 0;
}