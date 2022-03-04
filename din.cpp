#include <bits/stdc++.h>

using namespace std;

typedef struct sNode *Node;

struct sNode {
    int prior, cnt;
    char leftmost_nuc, rightmost_nuc, nuc;
    int leftmost_cnt, rightmost_cnt;
    bool one_nuc_only;
    int real_max;
    bool lazy;
    Node l, r;

    sNode() {}

    sNode(char _nuc) : prior(rand()), cnt(1), leftmost_nuc('Z'),
                       rightmost_nuc('Z'),
                       nuc(_nuc), leftmost_cnt(1), rightmost_cnt(1),
                       one_nuc_only(true),
                       real_max(1), lazy(false), l(nullptr), r(nullptr) {}
};

int cnt(Node n) {
    return n ? n->cnt : 0;
}

void upd_cnt(Node n) {
    if (n)
        n->cnt = 1 + cnt(n->l) + cnt(n->r);
}

void upd_vals_both_sons(Node n) {
    if (!n->l->one_nuc_only || n->nuc != n->l->nuc ||
        !n->r->one_nuc_only || n->nuc != n->r->nuc)
        n->one_nuc_only = false;
    else
        n->one_nuc_only = true;
    n->real_max = 1;
    if (n->l->lazy) {
        n->leftmost_nuc = n->l->rightmost_nuc;
        n->leftmost_cnt = n->l->rightmost_cnt;
    } else {
        n->leftmost_nuc = n->l->leftmost_nuc;
        n->leftmost_cnt = n->l->leftmost_cnt;
    }
    if (n->r->lazy) {
        n->rightmost_nuc = n->r->leftmost_nuc;
        n->rightmost_cnt = n->r->leftmost_cnt;
    } else {
        n->rightmost_nuc = n->r->rightmost_nuc;
        n->rightmost_cnt = n->r->rightmost_cnt;
    }

    if (n->l->one_nuc_only && n->l->nuc == n->nuc)
        n->leftmost_cnt++;
    if (n->r->one_nuc_only && n->r->nuc == n->nuc)
        n->rightmost_cnt++;
    if (n->one_nuc_only) {
        n->real_max = max(n->real_max, n->rightmost_cnt + n->leftmost_cnt - 1);
    }

    int candidate = 1;
    if (n->l->lazy) {
        if (n->nuc == n->l->leftmost_nuc) {
            if (n->r->leftmost_nuc == n->l->leftmost_nuc && n->r->one_nuc_only)
                n->rightmost_cnt += n->l->leftmost_cnt;
            candidate += n->l->leftmost_cnt;
        }
    } else {
        if (n->nuc == n->l->rightmost_nuc) {
            if (n->r->leftmost_nuc == n->l->rightmost_nuc && n->r->one_nuc_only)
                n->rightmost_cnt += n->l->rightmost_cnt;
            candidate += n->l->rightmost_cnt;
        }
    }
    if (n->r->lazy) {
        if (n->nuc == n->r->rightmost_nuc) {
            if (n->l->rightmost_nuc == n->r->rightmost_nuc &&
                n->l->one_nuc_only)
                n->leftmost_cnt += n->r->rightmost_cnt;
            candidate += n->r->rightmost_cnt;
        }
    } else {
        if (n->nuc == n->r->leftmost_nuc) {
            if (n->l->rightmost_nuc == n->r->leftmost_nuc && n->l->one_nuc_only)
                n->leftmost_cnt += n->r->leftmost_cnt;
            candidate += n->r->leftmost_cnt;
        }
    }

    int candidate2 = max(max(n->l->real_max, n->r->real_max),
                         max(n->leftmost_cnt, n->rightmost_cnt));
    n->real_max = max(n->real_max, candidate);
    n->real_max = max(n->real_max, candidate2);
}

void upd_vals_left_son_only(Node n) {
    if (!n->l->one_nuc_only || n->nuc != n->l->nuc)
        n->one_nuc_only = false;
    else
        n->one_nuc_only = true;
    if (n->l->lazy) {
        n->leftmost_nuc = n->l->rightmost_nuc;
        n->leftmost_cnt = n->l->rightmost_cnt;
    } else {
        n->leftmost_nuc = n->l->leftmost_nuc;
        n->leftmost_cnt = n->l->leftmost_cnt;
    }
    n->rightmost_nuc = n->nuc;
    n->rightmost_cnt = 1;

    if (n->l->one_nuc_only && n->l->nuc == n->nuc)
        n->leftmost_cnt++;
    if (n->l->lazy) {
        if (n->nuc == n->l->leftmost_nuc) {
            if (n->l->one_nuc_only)
                n->rightmost_cnt += n->l->real_max;
            else
                n->rightmost_cnt += n->l->leftmost_cnt;
        }
    } else {
        if (n->nuc == n->l->rightmost_nuc) {
            if (n->l->one_nuc_only)
                n->rightmost_cnt += n->l->real_max;
            else
                n->rightmost_cnt += n->l->rightmost_cnt;
        }
    }
    n->real_max = max(n->l->real_max,
                      max(n->leftmost_cnt, n->rightmost_cnt));
}

void upd_vals_right_son_only(Node n) {
    if (!n->r->one_nuc_only || n->nuc != n->r->nuc)
        n->one_nuc_only = false;
    else
        n->one_nuc_only = true;
    if (n->r->lazy) {
        n->rightmost_nuc = n->r->leftmost_nuc;
        n->rightmost_cnt = n->r->leftmost_cnt;
    } else {
        n->rightmost_nuc = n->r->rightmost_nuc;
        n->rightmost_cnt = n->r->rightmost_cnt;
    }
    n->leftmost_nuc = n->nuc;
    n->leftmost_cnt = 1;
    if (n->r->one_nuc_only && n->r->nuc == n->nuc)
        n->rightmost_cnt++;
    if (n->r->lazy) {
        if (n->nuc == n->r->rightmost_nuc) {
            if (n->r->one_nuc_only)
                n->leftmost_cnt += n->r->real_max;
            else
                n->leftmost_cnt += n->r->rightmost_cnt;
        }
    } else {
        if (n->nuc == n->r->leftmost_nuc) {
            if (n->r->one_nuc_only)
                n->leftmost_cnt += n->r->real_max;
            else
                n->leftmost_cnt += n->r->leftmost_cnt;
        }
    }
    n->real_max = max(n->r->real_max,
                      max(n->leftmost_cnt, n->rightmost_cnt));
}

void upd_vals_no_sons(Node n) {
    n->leftmost_nuc = n->nuc;
    n->rightmost_nuc = n->nuc;
    n->rightmost_cnt = 1;
    n->leftmost_cnt = 1;
    n->real_max = 1;
    n->one_nuc_only = true;
}

void upd_vals(Node n) {
    if (n) {
        if (n->l && n->r) {
            upd_vals_both_sons(n);
        } else if (n->l) {
            upd_vals_left_son_only(n);
        } else if (n->r) {
            upd_vals_right_son_only(n);
        } else {
            upd_vals_no_sons(n);
        }
    }
}

// Aktualizowanie dodanych do struktury atrybutów.
void upd(Node n) {
    upd_cnt(n);
    upd_vals(n);
}

void push(Node n) {
    if (n && n->lazy) {
        n->lazy = false;
        swap(n->l, n->r);
        if (n->l) n->l->lazy ^= true;
        if (n->r) n->r->lazy ^= true;
    }
}

void split(Node n, Node &l, Node &r, int key, int add = 0) {
    if (!n)
        return void(l = r = nullptr);
    push(n);
    int cur_key = add + cnt(n->l);
    if (key <= cur_key)
        split(n->l, l, n->l, key, add), r = n;
    else
        split(n->r, n->r, r, key, add + 1 + cnt(n->l)), l = n;
    upd(n);
}

void merge(Node &n, Node l, Node r) {
    push(l);
    push(r);
    if (!l || !r)
        n = l ? l : r;
    else if (l->prior > r->prior)
        merge(l->r, l->r, r), n = l;
    else
        merge(r->l, l, r->l), n = r;
    upd(n);
}

void heapify(Node n) {
    if (n) {
        Node max = n;
        if (n->l != nullptr && n->l->prior > max->prior)
            max = n->l;
        if (n->r != nullptr && n->r->prior > max->prior)
            max = n->r;
        if (max != n) {
            swap(n->prior, max->prior);
            heapify(max);
        }
    }
}

// Budowanie (w miarę) zrównoważonego treapa.
Node build(char *a, int k) {
    if (k == 0)
        return nullptr;
    int mid = k / 2;
    Node n = new sNode(a[mid]);
    n->l = build(a, mid);
    n->r = build(a + mid + 1, k - mid - 1);
    heapify(n);
    upd(n);
    return n;
}

// Operacja odwrócenia treapa na indeksach od j włącznie do k włącznie.
void O(Node n, const int &j, const int &k) {
    Node t1, t2, t3;
    split(n, t1, t2, j);
    split(t2, t2, t3, k - j + 1);
    t2->lazy ^= true;
    merge(n, t1, t2);
    merge(n, n, t3);
}

// Operacja wyjęcia z treapa znaków z indeksów [j, k] i wstawienie
// do pozostałej części DNA na pozycję l.
void P(Node n, const int &j, const int &k, const int &l) {
    if (j != l) {
        O(n, j, k);
        if (l < j) {
            O(n, l, j - 1);
            O(n, l, k);
        } else {
            O(n, k + 1, k + l - j);
            O(n, j, k + l - j);
        }
    }
}

// Operacja znalezienia najdłuższego stałego podciągu na indeksach [j, k].
void N(Node n, const int &j, const int &k) {
    Node t1, t2, t3;
    split(n, t1, t2, j);
    split(t2, t2, t3, k - j + 1);
    cout << t2->real_max << '\n';
    merge(n, t1, t2);
    merge(n, n, t3);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    char arr[n];
    char nuc;
    for (int i = 0; i < n; ++i) {
        cin >> nuc;
        arr[i] = nuc;
    }
    Node root = build(arr, n);
    char operation;
    int arg1, arg2, arg3;
    for (int i = 0; i < m; ++i) {
        cin >> operation;
        if (operation == 'O') {
            cin >> arg1 >> arg2;
            O(root, arg1 - 1, arg2 - 1);
        } else if (operation == 'N') {
            cin >> arg1 >> arg2;
            N(root, arg1 - 1, arg2 - 1);
        } else {
            cin >> arg1 >> arg2 >> arg3;
            P(root, arg1 - 1, arg2 - 1, arg3 - 1);
        }
    }
}