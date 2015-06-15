#include<bits/stdc++.h>
using namespace std;
int n,k;
int f[11][1001];
int g[1001][1001];
int w[1001];
int main(){
	freopen("bzoj1587.in","r",stdin);
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&w[i]);
		f[1][i]=f[1][i-1]+w[i]*(i-1);
	}
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)
		g[i][j]=g[i][j-1]+w[j]*(j-i);
	for(int i=2;i<=k;i++)
	for(int j=i;j<=n;j++){
		f[i][j]=1e9;
		for(int l=i;l<=j;l++)
			f[i][j]=min(f[i][j],f[i-1][l-1]+g[l][j]);
	}
	cout<<f[k][n]<<endl;
	return 0;
}
