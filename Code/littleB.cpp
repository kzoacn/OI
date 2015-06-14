#include<bits/stdc++.h>
using namespace std;
const int maxn=50010,maxK=5001;
int n,m,K;
int mp[maxn],a[maxn];
int sum[maxK][maxn];
int sqr(int x){return x*x;}
int main(){
	srand(time(0)^(long long)(new int));
	scanf("%d%d",&n,&m);K=maxK-1;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int _=1;_<=K;_++){
		for(int i=1;i<=n;i++)mp[i]=rand()%2?1:-1;
		for(int i=1;i<=n;i++)sum[_][i]=sum[_][i-1]+mp[a[i]];
	}while(m--){
		int res[maxK],rausen=maxK;
		int l,r;scanf("%d%d",&l,&r);
		for(int i=1;i<=K;i++)res[i]=sqr(sum[i][r]-sum[i][l-1]);
		long double ans=accumulate(res+1+K/rausen,res+1+K-K/rausen,.0);
		int len=K-K/rausen-K/rausen;
		printf("%d\n",int(ans/len+.5));
	}
	return 0;
}
