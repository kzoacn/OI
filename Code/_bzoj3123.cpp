/**
* @Author:kAc @ Qingdao No.2 Middle School
* @Version:1.0.0
* @Algorithm:Functional Segment Tree + Heuristic Merger
* Standard Program For Shandong Team Selection Contest Round 1 Day 1 Problem 2
*/
#include <algorithm>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 300001;
struct Tnode{
    int l, r, lc, rc, sum;
} a[30000001]; int tot;
int n, m, Q, val[MAXN], seg[MAXN];
int tot2, e[MAXN], v[MAXN], next[MAXN], f[MAXN][20], dep[MAXN];
struct Tdiscre{
    int data[MAXN], n;
    int & operator [] (int k) { return data[k]; }
    void init()
    {
        sort(data + 1, data + n + 1); 
        n = unique(data + 1, data + n + 1) - data - 1;
    }
    int convert(int d) { return lower_bound(data + 1, data + n + 1, d) - data; }
} dis;
struct Tuf{
	int f[1000001];
	int find(int a) { return f[a] == a ? a : f[a] = find(f[a]); }
} uf;
int size[MAXN];
int c, k;
int build(int l, int r)
{
    int now = ++tot; a[now].l = l; a[now].r = r; if (l == r) return now;
    a[now].lc = build(l, l + r >> 1); a[now].rc = build(l + r + 2 >> 1, r);
    return now;
}
int change(int now, int x, int y)
{
    a[++tot] = a[now]; a[tot].sum += y; now = tot;
    if (a[now].l == a[now].r) return tot;
    int m = a[now].l + a[now].r >> 1;
    if (x <= m) a[now].lc = change(a[now].lc, x, y); else a[now].rc = change(a[now].rc, x, y);
    return now;
}
void add(int a, int b) { ++tot2; next[tot2] = e[a]; e[a] = tot2; v[tot2] = b; }
bool vis[MAXN];
int now;
void dfs(int x, int nowseg)
{
    vis[x] = true; uf.f[x] = now; size[now]++;
    seg[x] = change(nowseg, val[x], 1);
	for (int i = 1; i < 20; i++) f[x][i] = 0;
    for (int i = 1; f[x][i - 1]; i++) f[x][i] = f[f[x][i - 1]][i - 1];
    for (int i = e[x]; i; i = next[i]) if (v[i] != f[x][0]){
        f[v[i]][0] = x; dep[v[i]] = dep[x] + 1; dfs(v[i], seg[x]);
    }
}
int lca(int x, int y)
{
    if (dep[x] < dep[y]) swap(x, y); int k = dep[x] - dep[y];
    for (int i = 0; i < 20; i++) if ((k >> i) & 1) x = f[x][i];
    if (x == y) return x;
    for (int i = 19; i >= 0; i--) if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    return f[x][0];
}
int getkth(int seg1, int seg2, int seg3, int k)
{
    if (a[seg1].l == a[seg1].r) return dis[a[seg1].l];
    int m = a[seg1].l + a[seg1].r >> 1, l = a[seg1].l;
    int tsum = a[a[seg1].lc].sum + a[a[seg2].lc].sum - a[a[seg3].lc].sum * 2 + (m >= val[c] && val[c] >= l);
    if (tsum >= k)
        return getkth(a[seg1].lc, a[seg2].lc, a[seg3].lc, k);
    else return getkth(a[seg1].rc, a[seg2].rc, a[seg3].rc, k - tsum);
}
int empty;

int main()
{
    //freopen("forest.in", "r", stdin); freopen("forest.out", "w", stdout); 
    scanf("%*d%d%d%d", &n, &m, &Q);
    for (int i = 1; i <= n; i++) scanf("%d", &val[i]);
    for (int i = 1; i <= n; i++) dis[i] = val[i]; dis.n = n; dis.init();
    for (int i = 1; i <= n; i++) val[i] = dis.convert(val[i]);
    for (int i = 1; i <= m; i++){
        int a, b; scanf("%d%d", &a, &b);
        add(a, b); add(b, a);
    }
    empty = build(1, dis.n);
    for (int i = 1; i <= n; i++) if (!vis[i]){
        now = i;
        dfs(i, empty);
    }
    int lastans = 0;
    while(Q--){
        scanf(" "); char op = getchar();
        if (op == 'Q'){
            int a, b;
//            if (Q % 10000 == 0) cerr << Q <<" " << tot << endl;
            scanf("%d%d%d", &a, &b, &k); a ^= lastans; b ^= lastans; k ^= lastans;
            c = lca(a, b);
            printf("%d\n", lastans = getkth(seg[a], seg[b], seg[c], k));
            lastans = 0;
        }
        else{
//		    if (Q % 10000 == 0) cerr << Q <<" " << tot << endl;
            int a, b; scanf("%d%d", &a, &b); a ^= lastans; b ^= lastans;
            int aa = uf.find(a), bb = uf.find(b);
            if (aa == bb){
                cerr <<"Fuck" << endl;
                while(1);
            }
            if (size[aa] < size[bb]) { swap(a, b); swap(aa, bb); }
            now = aa;
            f[b][0] = a; size[b] = 0; dep[b] = dep[a] + 1;
            dfs(b, seg[a]);
            add(a, b); add(b, a);
        }
    }
	cerr << tot << endl;
}
