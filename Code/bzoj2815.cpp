#include<bits/stdc++.h>
using namespace std;
const int maxn=65536;
const int BIT=17;
int n,in[maxn];
vector<int>G[maxn],Ge[maxn],GG[maxn];
int fa[maxn][BIT],siz[maxn],dep[maxn];
void make(int u){
	for(int i=1;i<BIT;i++)
		fa[u][i]=fa[fa[u][i-1]][i-1];
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);int d=dep[u]-dep[v];
	for(int i=BIT-1;i>=0;i--)if(d>>i&1)u=fa[u][i];
	if(u==v)return u;
	for(int i=BIT-1;i>=0;i--)if(fa[u][i]!=fa[v][i])
		u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}
void dfs(int u){
	siz[u]=1;
	for(int i=0;i<Ge[u].size();i++){
		int v=Ge[u][i];
		dfs(v);siz[u]+=siz[v];
	}
}
int top[maxn],size;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(;;){
			int x;scanf("%d",&x);if(!x)break;
			G[i].push_back(x);in[i]++;GG[x].push_back(i);
		}if(!G[i].size())G[i].push_back(n+1),fa[i][0]=n+1,in[i]++,GG[n+1].push_back(i);
	}queue<int>q;q.push(n+1);
	while(!q.empty()){
		int u=q.front();q.pop();
		top[size++]=u;
		for(int i=0;i<GG[u].size();i++){
			int v=GG[u][i];
			if(!--in[v])q.push(v);
		}
	}
	for(int i=1;i<size;i++){
		int u=top[i];
		int LCA=G[u][0];
		for(int i=1;i<G[u].size();i++)
			LCA=lca(LCA,G[u][i]);
		Ge[LCA].push_back(u);
//		cerr<<LCA<<" "<<u<<endl;
		fa[u][0]=LCA;dep[u]=dep[LCA]+1;
		make(u);
	}dfs(n+1);
	for(int i=1;i<=n;i++)printf("%d\n",siz[i]-1);
	return 0;
}
