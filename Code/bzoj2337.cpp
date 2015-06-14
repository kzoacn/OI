#include<bits/stdc++.h>
using namespace std;
const int maxn=105;
double a[maxn][maxn];
int n,m;
struct edge{int u,v,w;};
edge edges[int(1e4)];
double in[maxn];
double Gauss(int bit){
	memset(a,0,sizeof a);
	for(int i=1;i<n;i++)a[i][i]=-in[i];
	for(int i=0;i<m;i++){
		int u=edges[i].u,v=edges[i].v,w=edges[i].w;
		if(w>>bit&1){
			a[u][n+1]+=-1;
			a[u][v]+=-1;
			if(u==v)continue;
			a[v][n+1]+=-1;
			a[v][u]+=-1;
		}else{
			a[u][v]+=1;
			if(u==v)continue;
			a[v][u]+=1;
		}
	}memset(a[n],0,sizeof a[n]);
	a[n][n]=1;
	for(int i=1;i<=n;i++){
		int r=i;
		for(int j=i;j<=n;j++)if(fabs(a[j][i])>fabs(a[r][i]))r=j;
		for(int j=1;j<=n+1;j++)swap(a[r][j],a[i][j]);
		for(int j=i+1;j<=n;j++){
			double t=a[j][i]/a[i][i];
			for(int k=i;k<=n+1;k++)
				a[j][k]-=t*a[i][k];
		}
	}
	for(int i=n-1;i>=1;i--){
		for(int j=i+1;j<=n;j++)	
			a[i][n+1]-=a[j][n+1]*a[i][j];
		a[i][n+1]/=a[i][i];
	}
	return a[1][n+1];
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		scanf("%d%d%d",&edges[i].u,&edges[i].v,&edges[i].w);
		in[edges[i].u]++;
		if(edges[i].u!=edges[i].v)
		in[edges[i].v]++;
	}
	double ans=0;
	for(int bit=0;bit<31;bit++)
		ans+=(1<<bit)*Gauss(bit);
	printf("%.3lf\n",ans);
	return 0;
}
