#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;
 
#define N 1010
int n;
long long a[N];
int w[N], ins[64], sav[N], top;
 
int main() {
    scanf("%d", &n);
     
    register int i, j, k;
    for(i = 1; i <= n; ++i)
        scanf("%lld%d", &a[i], &w[i]);
    for(i = 1; i <= n; ++i)
        for(j = i + 1; j <= n; ++j)
            if (w[i] < w[j])
                swap(w[i], w[j]), swap(a[i], a[j]);
     
    int ans = 0;
    for(i = 1; i <= n; ++i) {
        for(j = 63; j >= 0; --j) {
            if ((a[i] >> j) & 1) {
                if (!ins[j]) {
                    ins[j] = i;
                    for(k = 1; k <= top; ++k)
                        if ((a[sav[k]] >> j) & 1)
                            a[sav[k]] ^= a[i];
                    sav[++top] = i;
                    break;
                }
                else
                    a[i] ^= a[ins[j]];
            }
        }
        if (a[i])
            ans += w[i];
    }
     
    printf("%d\n", ans);
     
    return 0;
}
