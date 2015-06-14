#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
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
int main(){
	
	return 0;
}
