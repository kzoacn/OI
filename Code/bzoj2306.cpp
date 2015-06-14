#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> par;
par edges[1001];
int n,m,s;
double w[101],p;
int mp[101][101];
double f[101][101][63],pw[63];
int vis[101][101][63];
vector<int>G[101];
double dfs(int s,int t,int d){
	if(vis[s][t][d])return f[s][t][d];
//	if(d==0&&mp[s][t]==1)return f[s][t][d]=w[s]+p*w[t];
//	if(d==0&&mp[s][t]!=1)return f[s][t][d]=0;
	for(int i=1;i<=m;i++){
		int u=edges[i].first,v=edges[i].second;
		if(mp[s][u]+1+mp[v][t]<=(1<<d))
		f[s][t][d]=max(f[s][t][d],dfs(s,u,d-1)+pw[d-1]*dfs(v,t,d-1));
	}
	vis[s][t][d]=1;
	return f[s][t][d];
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>w[i];
	cin>>s;
	cin>>p;
	for(int i=0;i<=62;i++)pw[i]=pow(p,pow(2,i));
	memset(mp,0x3f,sizeof mp);
	for(int i=1;i<=n;i++)mp[i][i]=0;
	for(int i=1;i<=m;i++){
		int u,v;cin>>u>>v;
		G[u].push_back(v);
		mp[u][v]=1;edges[i]=par(u,v);
		vis[u][v][0]=1;
		f[u][v][0]=w[u]+w[v]*p;
	}double ans=0;
	for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	mp[i][j]=min(mp[i][j],mp[i][k]+mp[k][j]);
	for(int i=1;i<=n;i++)ans=max(ans,dfs(s,i,3));
	printf("%.1lf\n",ans);
	return 0;
}
