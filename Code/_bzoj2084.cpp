#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
 
const int maxn = 20000100;
int n; long long ans = 0;
char s[maxn];
int st[maxn];
 
void read() {
    scanf("%d", &n);
    scanf("%s", s + 1);
    for(int i = 1; i <= n; ++ i) st[i << 1] = (s[i] == '0' ? 0 : 2);
    n <<= 1; ++ n;
    for(int i = 1; i <= n; i += 2) st[i] = 1;
}
 
int p[maxn];
 
void sov() {
    int mx, id; mx = 0, id = 0;
    for(int i = 1; i <= n; i += 2) {
        if(mx > i) p[i] = min(p[2 * id - i], mx - i);
        else p[i] = 1;
        for(; i - p[i] > 0 && i + p[i] <= n && st[i - p[i]] + st[i + p[i]] == 2; ++ p[i]);
        if(i + p[i] > mx) mx = i + p[i], id = i;
    }
    for(int i = 1; i <= n; i += 2) ans += (long long)((p[i] - 1) >> 1);
    printf("%lld\n", ans);
}
 
int main() {
    //freopen("test.in", "r", stdin);
    read(), sov();
    return 0;
}
