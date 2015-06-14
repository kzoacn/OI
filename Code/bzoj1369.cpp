#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4+5;
int f[maxn][3];
vector<int>G[maxn];
int fa[maxn],vis[maxn][3];
int dfs(int u,int o){
	if(vis[u][o])return f[u][o];
	f[u][o]=o;vis[u][o]=1;
	for(int v,i=0;i<G[u].size();i++){
		if(fa[u]==(v=G[u][i]))continue;
		fa[v]=u;
		f[u][o]+=min(dfs(v,(o+1)%3),dfs(v,(o+2)%3));
	}return f[u][o];
}int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	cout<<n+min(dfs(1,0),min(dfs(1,1),dfs(1,2)))<<endl;
	return 0;
}
