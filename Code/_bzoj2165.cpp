#include <cstdio>
#include <cstring>

typedef long long LL;

const int MAXN = 111, MAXC = 66;

LL g[MAXC][MAXN][MAXN], p[MAXN][MAXN], q[MAXN][MAXN];

inline void checkmax(LL &x, LL y) {
    if (y > x)
        x = y;
}

inline void checkmin(LL &x, LL y) {
    if (y < x)
        x = y;
}

inline void work() {
    int n, c;
    LL m, ans = 1, t = 0;
    scanf("%d%lld", &n, &m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            scanf("%lld", &g[0][i][j]);
            checkmin(g[0][i][j], m);
            if (!i)
                checkmax(t, g[0][i][j]);
        }
    if (t == m) {
        puts("1");
        return;
    }
    for (c = 1; c < MAXC; ++c) {
        t = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                g[c][i][j] = 0;
                for (int k = 0; k < n; ++k)
                    if (g[c - 1][i][k] && g[c - 1][k][j])
                        checkmax(g[c][i][j], g[c - 1][i][k] + g[c - 1][k][j]);
                checkmin(g[c][i][j], m);
                if (!i)
                    checkmax(t, g[c][i][j]);
            }
        if (t == m)
            break;
    }
    memcpy(p, g[--c], sizeof p);
    for (ans += 1LL << c--; c >= 0; --c) {
        t = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                q[i][j] = 0;
                for (int k = 0; k < n; ++k)
                    if (p[i][k] && g[c][k][j])
                        checkmax(q[i][j], p[i][k] + g[c][k][j]);
                checkmin(q[i][j], m);
                if (!i)
                    checkmax(t, q[i][j]);
            }
        if (t < m) {
            ans += 1LL << c;
            memcpy(p, q, sizeof q);
        }
    }
    printf("%lld\n", ans);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--)
        work();
    return 0;
}
