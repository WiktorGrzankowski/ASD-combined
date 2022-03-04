#include <iostream>

using namespace std;


void init(long long tree[], long long n) {
    for (long long i = 0; i < 2 * n; ++i) {
        tree[i] = 0;
    }
}

void build(long long tree[], long long A[], long long node, long long start, long long end) {
    if (start == end) {
        tree[node] = A[start + 1];
    } else {
        long long mid = (start + end) / 2;
        build(tree, A, 2 * node, start, mid); // left child
        build(tree, A, 2 * node + 1, mid + 1, end); // right child
        tree[node] = (tree[2 * node] + tree[2 * node + 1])% 1000000000; // sum of children
    }
}

void modify(long long tree[], long long node, long long nodeL, long long nodeR, long long idx, long long val) {
    if (nodeL == nodeR) {
        // Leaf node
        tree[node] += val;
    } else {
        long long mid = (nodeL + nodeR) / 2;
        if (nodeL <= idx && idx <= mid) {
            // If idx is in the left child, recurse on the left child
            modify(tree, 2 * node, nodeL, mid, idx, val);
        } else {
            // If idx is in the right child, recurse on the right child
            modify(tree, 2 * node + 1, mid + 1, nodeR, idx, val);
        }
        tree[node] = (tree[2 * node] + tree[2 * node + 1]) % 1000000000;
    }
}

// node spreads from start to end
// we find sum of range l to r
long long query(long long tree[], long long node, long long nodeL, long long nodeR, long long l, long long r) {
    if (r < nodeL || nodeR < l)
        return 0; // range of node is completely outside the given range

    if (l <= nodeL && nodeR <= r)
        return tree[node];

    // range represented by a node is partially inside and partially
    // outside the given range
    long long mid = (nodeL + nodeR) / 2;
    return (query(tree, 2 * node, nodeL, mid, l, r)
           + query(tree, 2 * node + 1, mid + 1, nodeR, l, r)) % 1000000000;
}


long long nearestPow2(long long v) {
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
    long long n, k;
    cin >> n >> k;
    long long A[n + 1];
    A[0] = 0;
    for (long long i = 1; i < n + 1; ++i) {
        cin >> A[i]; // index 0 is ignored
    }

    long long treeBase = nearestPow2(n);
    long long tree[2 * treeBase];

    long long t[n + 1][k + 1]; // 0 on both indices is ignored
    for (long long i = 0; i < n + 1; ++i) {
        for (long long j = 0; j < k + 1; ++j) {
            if (i != 0 && j == 1)
                t[i][j] = 1;
            else
                t[i][j] = 0;
        }
    }
    for (long long l = 2; l < k + 1; ++l) {
        init(tree, treeBase);
        for (long long i = 1; i < n + 1; ++i) {
            t[i][l] = query(tree, 1, 1, n, A[i] + 1, n);
            modify(tree, 1, 1, n, A[i], t[i][l - 1]);
        }
    }
    long long res = 0;
    for (long long i = 1; i < n + 1; ++i) {

        res += t[i][k] % 1000000000;
    }
    cout << res % 1000000000;

    return 0;
}
