#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int f[maxn],g[maxn],siz[maxn];
int n,m,fa[maxn];
vector<int>G[maxn];
void dfs(int u){
	siz[u]=1==G[u].size()&&u!=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(fa[u]==v)continue;
		fa[v]=u;
		dfs(v);
		siz[u]+=siz[v];
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
//		G[v].push_back(u);
	}
	dfs(1);
	cout<<dpmax[1]+1<<" "<<dpmin[1]+1<<endl;	
	return 0;
}
