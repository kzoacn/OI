#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;
#define N 300000 + 5
#define M 42000000 + 5

int n, m, tot, cnt, Head[N], Root[N];

struct Chain
{
    int next, node;
}E[N];

struct Node
{
    int l, r;
    bool d, flag;
}h[M];

inline int getint()
{
    char ch = '\n';
    for (; ch > '9' || ch < '0'; ch = getchar()) ;
    int res = ch - '0';
    for (ch = getchar(); ch >= '0' && ch <= '9'; ch = getchar())
        res = (res << 3) + (res << 1) + ch - '0';
    return res;
}

inline void addedge(int u, int v)
{
    E[++ tot].next = Head[u];
    Head[u] = tot;
    E[tot].node = v;
}

inline int Inc(int a, int b)
{
    return a + b - (a + b >= n ? n : 0) + 1;
}

inline void update(int x)
{
    h[x].flag = h[h[x].l].flag | h[h[x].r].flag;
}

inline void apply(int x)
{
    h[x].d = h[x].flag = 1;
}

inline void Modify(int &x, int t, int b, int l, int r, int st, int sb, int sl, int sr)
{
    h[++ cnt] = h[x];
    x = cnt;
    if (t == st && b == sb && l == sl && r == sr)
    {
        apply(x);
        return ;
    }
    if (h[x].d) return ;
    if (b - t >= r - l)
    {
        int mid = t + b >> 1;
        if (sb <= mid) Modify(h[x].l, t, mid, l, r, st, sb, sl, sr);
            else if (st > mid) Modify(h[x].r, mid + 1, b, l, r, st, sb, sl, sr);
            else Modify(h[x].l, t, mid, l, r, st, mid, sl, sr), Modify(h[x].r, mid + 1, b, l, r, mid + 1, sb, sl, sr);
    }
    else if (b - t < r - l)
    {
        int mid = l + r >> 1;
        if (sr <= mid) Modify(h[x].l, t, b, l, mid, st, sb, sl, sr);
            else if (sl > mid) Modify(h[x].r, t, b, mid + 1, r, st, sb, sl, sr);
            else Modify(h[x].l, t, b, l, mid, st, sb, sl, mid), Modify(h[x].r, t, b, mid + 1, r, st, sb, mid + 1, sr);
    }
    update(x);
}

inline bool Query(int x, int t, int b, int l, int r, int u, int v)
{
    if (!h[x].flag) return 0;
    if (h[x].d) return 1;
    if (t == b && l == r)
        return h[x].flag;
    if (b - t >= r - l)
    {
        int mid = t + b >> 1;
        if (u <= mid) return Query(h[x].l, t, mid, l, r, u, v);
            else return Query(h[x].r, mid + 1, b, l, r, u, v);
    }
    else if (b - t < r - l)
    {
        int mid = l + r >> 1;
        if (v <= mid) return Query(h[x].l, t, b, l, mid, u, v);
            else return Query(h[x].r, t, b, mid + 1, r, u, v);
    }
}

int main()
{
    n = getint(), m = getint();
    for (int i = 1; i <= n; i ++)
        addedge(i, 0);
    for (int i = 1; i <= n; i ++)
        addedge(getint(), i);
    for (int i = 1; i <= n; i ++)
        addedge(i, n + 1);
    for (int i = n; i; i --)
    {
        int a, b, c;
        a = E[Head[i]].node;
        b = E[Head[i] = E[Head[i]].next].node;
        Root[i] = Root[i + 1];
        while (E[Head[i]].next)
        {
            Head[i] = E[Head[i]].next;
            int c = E[Head[i]].node;
            Modify(Root[i], 1, n, 1, n, c + 1, b, b, a - 1);
            a = b, b = c;
        }
    }
    int last = 0;
    while (m --)
    {
        int x = Inc(getint(), last), y = Inc(getint(), last), l = 0, r = n;
        if (x > y) swap(x, y);
        while (l < r)
        {
            int mid = l + r + 1 >> 1;
            if (Query(Root[mid], 1, n, 1, n, x, y))
                l = mid;
            else r = mid - 1;
        }
        printf("%d\n", last = l);
        last=0;
    }cerr<<clock()/double(CLOCKS_PER_SEC)<<endl;
    
    return 0;
}
