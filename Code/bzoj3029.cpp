#include<bits/stdc++.h>
using namespace std;
int n,L,K;
double f[203][203][403];
double p[203];
int a[201];
int main(){
	scanf("%d%d%d",&n,&L,&K);K=min(K,n);
	for(int i=1;i<=n;i++)scanf("%lf",&p[i]),p[i]/=100.0;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	f[0][0][K+n]=1;
	double ans=0;
	for(int i=0;i<n;i++)
	for(int j=0;j<=i;j++)
	for(int k=0;k<=n*2;k++){
		f[i+1][j+1][max(min(k+a[i+1],n*2),0)]+=f[i][j][k]*p[i+1];
		f[i+1][j][k]+=f[i][j][k]*(1-p[i+1]);
	}
	for(int i=L;i<=n;i++)
	for(int j=n;j<=n*2;j++)
		ans+=f[n][i][j];
	printf("%.6f\n",ans);
	return 0;
}
