/**************************************************************
    Problem: 4025
    User: rausen
    Language: C++
    Result: Accepted
    Time:4344 ms
    Memory:6668 kb
****************************************************************/
 
#include <cstdio>
#include <algorithm>
 
using namespace std;
const int N = 1e5 + 5;
const int M = 2e5 + 5;
 
inline int read();
 
struct edge {
    int x, y, st, ed;
 
    inline void get() {
        x = read(), y = read();
        st = read() + 1, ed = read();
    }
} e[M];
 
int n, m, time;
 
namespace set {
    int fa[N], d[N], a[N];
    int s[N << 2], top = 0;
     
    int find(int x) {
        while (fa[x] != x) x = fa[x];
        return x;
    }
    int dep(int x) {
        static int res;
        for (res = 0; fa[x] != x; x = fa[x])
            res ^= a[x];
        return res;
    }
     
    void set_union(int x, int y, int _d) {
        if (d[x] > d[y]) swap(x, y);
        if (d[x] == d[y]) ++d[y], s[++top] = -y;
        fa[x] = y, a[x] = _d, s[++top] = x; 
    }
     
    void set_resume(int t) {
        for (; top != t; --top)
            if (s[top] < 0) --d[-s[top]];
            else fa[s[top]] = s[top], a[s[top]] = 0;
    }
}
using namespace set;
 
void work(int l, int r, int m) {
    int mid = l + r >> 1, now = top;
    int i, j, fx, fy, _d;
    for (i = 1; i <= m; ++i)
        if (e[i].st <= l && r <= e[i].ed) {
            fx = find(e[i].x), fy = find(e[i].y), _d = !(dep(e[i].x) ^ dep(e[i].y));
            if (fx != fy) set_union(fx, fy, _d);
            else if (_d) {
                while (l <= r)
                    puts("No"), ++l;
                set_resume(now);
                return;
            }
            swap(e[m--], e[i--]);
        };
    if (l == r) puts("Yes");
    else {
        for (i = 1, j = m; i <= j; ++i)
            if (e[i].st > mid) swap(e[j--], e[i--]);
        work(l, mid, j);
        for (i = 1, j = m; i <= j; ++i)
            if (e[i].ed <= mid) swap(e[j--], e[i--]);
        work(mid + 1, r, j);
    }
    set_resume(now);
}
 
int main() {
	freopen("bzoj4025.in","r",stdin);
    int i;
    n = read(), m = read(), time = read();
    for (i = 1; i <= n; ++i)
        fa[i] = i, d[i] = 1, a[i] = 0;
    for (i = 1; i <= m; ++i) e[i].get();
    for (i = 1; i <= m; ++i)
        if (e[i].st > e[i].ed) swap(e[i--], e[m--]);
    work(1, time, m);
    return 0;
}
 
inline int read() {
    static int x, sgn;
    static char ch;
    x = 0, sgn = 1, ch = getchar();
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
