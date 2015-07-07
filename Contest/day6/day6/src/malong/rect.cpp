#include <cstdio>
const int MAXN = 1005;

char buf[MAXN];
int n, g[MAXN][MAXN];

inline int min(int a, int b){return a > b ? b : a;}
inline int max(int a, int b){return a > b ? a : b;}
int main(){
	freopen("rect.in", "r", stdin);
	freopen("rect.out", "w", stdout);
	int i, j, a, b, c, d, e, f, G, h, ans = 0;
	scanf("%d", &n);
	for(i = 1; i <= n; ++ i){
		scanf("%s", buf + 1);
		for(j = 1; j <= n; ++ j)
			g[i][j] = g[i - 1][j] + g[i][j - 1] - g[i - 1][j - 1] + (buf[j] == 'C');
	}
	for(a = 1; a <= n; ++ a)
		for(b = 1; b <= n; ++ b)
			for(c = a; c <= n; ++ c)
				for(d = b; d <= n; ++ d){
					if((a == c && b == d) || (g[c][d] - g[c][b - 1] - g[a - 1][d] + g[a - 1][b - 1] != (c - a + 1) * (d - b + 1))) continue;
					for(e = 1; e <= n; ++ e)
						for(f = 1; f <= n; ++ f)
							for(G = e; G <= n; ++ G)
								for(h = f; h <= n; ++ h){
									if((e == G && f == h) || (g[G][h] - g[G][f - 1] - g[e - 1][h] + g[e - 1][f - 1] != (G - e + 1) * (h - f + 1))) continue;
									if(max(a, e) <= min(c, G) && max(b, f) <= min(d, h)) continue;
									ans ++;
								}
				}
	printf("%d\n", ans >> 1);
	return 0;
}
