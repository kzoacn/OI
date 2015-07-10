/**************************************************************
    Problem: 3276
    User: rausen
    Language: C++
    Result: Accepted
    Time:4884 ms
    Memory:19364 kb
****************************************************************/
 
#include <cstdio>
#include <algorithm>
 
using namespace std;
typedef long long ll;
const int N = 250005;
 
struct data {
    int w, p;
    ll d2, r2;
     
    inline bool operator < (const data &a) const {
        return d2 < a.d2;
    }
} a[N];
 
struct seg_node {
    int v;
    seg_node *son[2];
} *seg_root, mempool[N << 2], *cnt_seg = mempool, *null;
 
int n;
int q[N], H, T;
ll R2;
 
inline int lower() {
    int l = 1, r = n + 1, mid;
    while (l + 1 < r) {
        mid = l + r >> 1;
        if (a[mid].d2 <= R2) l = mid;
        else r = mid;
    }
    return l;   
}
 
inline int read() {
    int x = 0, sgn = 1;
    char ch = getchar();
    while (ch < '0' || '9' < ch) {
        if (ch == '-') sgn = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return sgn * x;
}
 
#define mid (l + r >> 1)
#define V p -> v
#define Ls p -> son[0]
#define Rs p -> son[1]
inline void new_node(seg_node *&p) {
    p = ++cnt_seg;
    V = 0, Ls = Rs = null;
}
 
inline int get_min(int x, int y) {
    if (!x) return y;
    if (!y) return x;
    return a[x].w < a[y].w ? x : y;
}
 
inline void update(seg_node *p) {
    V = get_min(Ls -> v, Rs -> v);
}
 
void seg_build(seg_node *&p, int l, int r) {
    new_node(p);
    if (l == r) {
        V = l;
        return;
    }
    seg_build(Ls, l, mid), seg_build(Rs, mid + 1, r);
    update(p);
}
 
void seg_modify(seg_node *p, int l, int r, int pos) {
    if (l == r) {
        V = 0;
        return;
    }
    if (pos <= mid) seg_modify(Ls, l, mid, pos);
    else seg_modify(Rs, mid + 1, r, pos);
    update(p);
}
 
int seg_query(seg_node *p, int l, int r, int pos) {
    if (r <= pos) return V;
    int res = seg_query(Ls, l, mid, pos);
    if (pos > mid) res = get_min(res, seg_query(Rs, mid + 1, r, pos));
    return res;
}
#undef mid
#undef V
#undef Ls
#undef Rs
 
inline ll sqr(ll x) {
    return x * x;
}
 
int main() {
 	freopen("bzoj3276.in","r",stdin);

    int X, Y, P, x, y, r, i, tmp, pos;
    null = cnt_seg, null -> son[0] = null -> son[1] = null, null -> v = 0;
    X = read(), Y = read(), P = read(), R2 = sqr(read()), n = read();
    for (i = 1; i <= n; ++i) {
        x = read(), y = read(), a[i].w = read(), a[i].p = read(), r = read();
        a[i].d2 = sqr(X - x) + sqr(Y - y), a[i].r2 = sqr(r);
    }
    sort(a + 1, a + n + 1);
    seg_build(seg_root, 1, n);
    while ((pos = lower()) != 0) {
        tmp = seg_query(seg_root, 1, n, pos);
        if (!tmp || a[tmp].w > P) break;
        seg_modify(seg_root, 1, n, tmp);
        q[++T] = tmp;
    }
    while (H <= T) {
        P = a[q[H]].p, R2 = a[q[H]].r2, ++H;
        while ((pos = lower()) != 0) {
            tmp = seg_query(seg_root, 1, n, pos);
            if (!tmp || a[tmp].w > P) break;
            seg_modify(seg_root, 1, n, tmp);
            q[++T] = tmp;
        }
    }
    printf("%d\n", T);
    return 0;
}

