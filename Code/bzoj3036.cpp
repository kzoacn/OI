#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
typedef pair<double,double> par;
int n,m,out[maxn],vis[maxn];
double f[maxn];
vector<pair<int,int> >G[maxn];
void dfs(int v){
	if(vis[v])return;
	for(int i=0;i<G[v].size();i++){
		int u=G[v][i].first,w=G[v][i].second;
		dfs(u);
		f[v]+=f[u]+w;
	}f[v]/=double(G[v].size()?G[v].size():1);vis[v]=1;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		G[u].push_back(pair<int,int>(v,w));
		out[u]++;
	}vis[n]=1;dfs(1);
	printf("%.2lf\n",f[1]);
	return 0;
}
