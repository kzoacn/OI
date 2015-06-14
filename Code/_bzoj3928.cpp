/**************************************************************
    Problem: 3928
    User: rausen
    Language: C++
    Result: Accepted
    Time:1820 ms
    Memory:2248 kb
****************************************************************/
 
#include <cstdio>
#include <algorithm>
 
using namespace std;
const int N = 605;
const int inf = 1e9;
 
inline int read();
 
struct data {
    int st, ed, h;
    data(int _s = 0, int _e = 0, int _h = 0) : st(_s), ed(_e), h(_h) {}
     
    inline void get() {
        st = read(), ed = read(), h = read();
    }
} a[N];
 
int n, tot;
int tmp[N], len;
int f[N][N];
 
int main() {
    int T, H, i, j, k;
    T = read();
    while (T--) {
        n = read();
        for (i = 1; i <= n; ++i) {
            a[i].get();
            tmp[i * 2 - 1] = a[i].st, tmp[i * 2] = a[i].ed;
        }
        sort(tmp + 1, tmp + 2 * n + 1);
        tot = unique(tmp + 1, tmp + 2 * n + 1) - tmp - 1;
        for (i = 1; i <= n; ++i) {
            a[i].st = lower_bound(tmp + 1, tmp + tot + 1, a[i].st) - tmp;
            a[i].ed = lower_bound(tmp + 1, tmp + tot + 1, a[i].ed) - tmp;
        }
        tot += 1;
        for (len = 0; len <= tot; ++len)
            for (i = 0; i <= tot - len; ++i) {
                j = i + len, H = -1;
                for (k = 1; k <= n; ++k)
                    if (i < a[k].st && a[k].ed < j && (H == -1 || a[H].h < a[k].h)) H = k;
                if (H == -1) f[i][j] = 0;
                else for (f[i][j] = inf, k = a[H].st; k <= a[H].ed; ++k)
                    f[i][j] = min(f[i][j], a[H].h + f[i][k] + f[k][j]);
            }
        printf("%d\n", f[0][tot]);
    }       
    return 0;
}
 
inline int read() {
    static int x;
    static char ch;
    x = 0, ch = getchar();
    while (ch < '0' || '9' < ch)
        ch = getchar();
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}
