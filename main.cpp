#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX_X = 1000005;
int max_val[MAX_X * 4];
int lazy_tag[MAX_X * 4];

void push_down(int node) {
    if (lazy_tag[node] != 0) {
        int left_child = node * 2;
        int right_child = node * 2 + 1;
        
        max_val[left_child] += lazy_tag[node];
        lazy_tag[left_child] += lazy_tag[node];
        
        max_val[right_child] += lazy_tag[node];
        lazy_tag[right_child] += lazy_tag[node];
        
        lazy_tag[node] = 0;
    }
}

void update(int node, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        max_val[node] += val;
        lazy_tag[node] += val;
        return;
    }
    push_down(node);
    int mid = l + (r - l) / 2;
    if (ql <= mid) {
        update(node * 2, l, mid, ql, qr, val);
    }
    if (qr > mid) {
        update(node * 2 + 1, mid + 1, r, ql, qr, val);
    }
    max_val[node] = max(max_val[node * 2], max_val[node * 2 + 1]);
}

int query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return max_val[node];
    }
    push_down(node);
    int mid = l + (r - l) / 2;
    int res = 0;
    if (ql <= mid) {
        res = max(res, query(node * 2, l, mid, ql, qr));
    }
    if (qr > mid) {
        res = max(res, query(node * 2 + 1, mid + 1, r, ql, qr));
    }
    return res;
}

// Fast I/O with fread
const int BUF_SIZE = 1 << 20;
char buf[BUF_SIZE], *p1 = buf, *p2 = buf;
inline char gc() {
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, BUF_SIZE, stdin), p1 == p2) ? EOF : *p1++;
}

inline int read() {
    int x = 0, f = 1;
    char ch = gc();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = gc();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = gc();
    }
    return x * f;
}

int main() {
    int x = read();
    int k = read();
    int p = read();
    
    for (int i = 0; i < p; ++i) {
        int u = read();
        int v = read();
        int n = read();
        
        if (u > v) {
            swap(u, v);
        }
        
        if (u == v) {
            putchar('T');
            putchar('\n');
            continue;
        }
        
        int max_used = query(1, 1, x - 1, u, v - 1);
        if (max_used + n <= k) {
            update(1, 1, x - 1, u, v - 1, n);
            putchar('T');
            putchar('\n');
        } else {
            putchar('N');
            putchar('\n');
        }
    }
    
    return 0;
}