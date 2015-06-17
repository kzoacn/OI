#include<bits/stdc++.h>
using namespace std;
const int maxn=100010; 
typedef unsigned long long UL;
struct edge{int u,v;};
int n,m,dep[maxn];
vector<edge>E;
vector<int>G[maxn];
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
void add(int u,int v){
	E.push_back((edge){u,v});
	G[u].push_back(E.size()-1);
	E.push_back((edge){v,u});
	G[v].push_back(E.size()-1);
}
int fa[maxn],vis[maxn];
UL ran(){
	return ((UL)rand()<<32)|(rand());
}
UL Ran[1000001],f[maxn];
void dfs(int u){
	vis[u]=1;
	for(int i=0;i<G[u].size();i++){
		edge e=E[G[u][i]];
		if(e.v==fa[u])continue;
		if(!vis[e.v]){
			fa[e.v]=u;
			dep[e.v]=dep[u]+1;
			dfs(e.v);
		}else if(dep[e.v]<dep[u]){
			Ran[G[u][i]]=Ran[G[u][i]^1]=ran();
			f[e.v]^=Ran[G[u][i]];
			f[u]^=Ran[G[u][i]];
		}
	}
}
void dfs2(int u){
	for(int i=0;i<G[u].size();i++){
		edge e=E[G[u][i]];
		if(fa[e.v]==u){
			dfs2(e.v);
			f[u]^=f[e.v];
			Ran[G[u][i]]=Ran[G[u][i]^1]^=f[e.v];
		}
	}
}
UL base[64];
int main(){
//	freopen("bzoj3563.in","r",stdin);
	n=in();m=in();
	for(int i=1;i<=m;i++){
		int u=in(),v=in();
		add(u,v);
	}dfs(1);
	dfs2(1);
	int q=in();
	int lans=0;
	while(q--){
		int k=in();
		int flag=1;
		memset(base,0,sizeof base);
		while(k--){
			UL x=Ran[((in()^lans)-1)<<1];
			for(int i=63;i>=0;i--){
				if(x>>i&1){
					if(base[i])x^=base[i];
					else {base[i]=x;break;}
				}
				if(!x)flag=0;
			}
		}lans+=flag;
		puts(flag?"Connected":"Disconnected");
	}
	return 0;
}
