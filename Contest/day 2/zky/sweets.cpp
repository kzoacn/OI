#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
const int mo=1e9+7;
int dp[1001][2001],sum[2001];
int a[1001];
int mx=0;
int Q[10001];
int n,m;
#define Sum(l,r) (sum[r]-(l?sum[l-1]:0))
int main(){
	freopen("sweets.in","r",stdin);
	freopen("sweets.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)scanf("%d",&Q[i]),mx=max(mx,Q[i]);
	dp[0][0]=1;
	for(int j=0;j<=mx;j++)sum[j]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=mx;j++)
			dp[i][j]=Sum(max(j-a[i],0),j);
		sum[0]=dp[i][0]%mo;
		for(int j=1;j<=mx;j++)
			sum[j]=(sum[j-1]+dp[i][j])%mo;		
	}	
	for(int i=1;i<=m;i++)
		printf("%d\n",dp[n][Q[i]]%mo);
	return 0;
}
