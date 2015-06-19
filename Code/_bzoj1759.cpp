#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
typedef long long LL;
int n,m;
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
int siz[maxn],son[maxn],fa[maxn],top[maxn],dep[maxn],mp[maxn],z;
vector<int>G[maxn];
LL anss[8];
void dfs(int u){
	siz[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==fa[u])continue;
		fa[v]=u;dep[v]=dep[u]+1;
		dfs(v);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])son[u]=v;
	}
}
int col[maxn];
void Q(int u,int v,int c){
	if(dep[u]<dep[v])swap(u,v);
	while(dep[u]>dep[v]){
		if(col[u]!=c)col[u]=c,anss[c]++;
		u=fa[u];
	}		
	while(u!=v){
		if(col[u]!=c)col[u]=c,anss[c]++;
		u=fa[u];
		if(col[v]!=c)col[v]=c,anss[c]++;
		v=fa[v];		
	}
	//if(col[v]!=c)col[v]=c,anss[c]++;
}
int main(){
//	freopen("bzoj1759.in","r",stdin);
	n=in();
	for(int i=1;i<n;i++){
		int u=in(),v=in();
		G[u].push_back(v);
		G[v].push_back(u);
	}dfs(1);
	int m=in();
	while(m--){
		int u=in(),v=in(),c=in();	
		Q(u,v,c);
	}
	for(int i=1;i<=7;i++)
		printf("%lld\n",anss[i]);
	return 0;
}
