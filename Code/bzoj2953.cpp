#include<bits/stdc++.h>
using namespace std;
const int maxn=30010;
vector<int>G[maxn];
int fa[maxn],top[maxn],siz[maxn],son[maxn],mp[maxn],z,dep[maxn];
void dfs(int u){
	siz[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v!=fa[u]){
			fa[v]=u;dep[v]=dep[u]+1;
			dfs(v);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])son[u]=v;
		}
	}
}
void build(int u,int tp){
	top[u]=tp;mp[u]=++z;
	if(son[u])build(son[u],tp);
	for(int v,i=0;i<G[u].size();i++)if((v=G[u][i])!=son[u]&&v!=fa[u])build(v,v);
}
int dis(int u,int v){
	int ans=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		ans+=dep[u]-dep[top[u]]+1;
		u=fa[top[u]];
	}if(dep[u]<dep[v])swap(u,v);
	ans+=dep[u]-dep[v];
	return ans;
}
int n,m;
int main(){
	freopen("bzoj2953.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}dfs(1);build(1,1);
	scanf("%d",&m);
	int u=1;
	long long ans=0;
	while(m--){
		int v;scanf("%d",&v);
		ans+=dis(u,v);
		u=v;
	}cout<<ans<<endl;
	return 0;
}
