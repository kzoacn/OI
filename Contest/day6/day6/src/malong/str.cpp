#include <cstdio>

int all[1000], bit[1000];

int main(){
	freopen("str.in", "r", stdin);
	freopen("str.out", "w", stdout);
	int i, j, tmp, cnt, n, k;
	scanf("%d%d", &n, &k);
	all[0] = 1;
	for(i = 1; i < n; ++ i) all[i] = all[i - 1] << 1 | 1;
	bit[0] = 1;
	for(i = 1; i < n; ++ i) bit[i] = bit[i - 1] << 1;
	for(i = 1, cnt = 0; i < (1 << n); ++ i){
		tmp = i;
		if((tmp ^ all[n - 1]) < tmp) continue;
		for(j = 1; j <= n / 2; ++ j)
			if(bool(tmp & (1 << (j - 1))) != bool(tmp & (1 << (n - j))))
				tmp ^= (1 << (j - 1)) ^ (1 << (n - j));
		if(tmp < i) continue;
		tmp = i ^ all[n - 1];
		for(j = 1; j <= n / 2; ++ j)
			if(bool(tmp & (1 << (j - 1))) != bool(tmp & (1 << (n - j))))
				tmp ^= (1 << (j - 1)) ^ (1 << (n - j));
		if(tmp < i) continue;
		cnt ++;
		if(cnt == k){
			for(j = n; j; -- j)
				putchar(bool((i & (1 << (j - 1)))) + '0');
			putchar('\n');
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}
