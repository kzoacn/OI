#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n;
vector<int>G[maxn];
int vis[maxn],col[maxn];
void add(int u,int v){G[u].push_back(v);G[v].push_back(u);}
void dfs(int u){
	vis[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(vis[v])continue;
		col[v]=col[u]^1;
		dfs(v);
	}
}
int X[maxn],Y[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x,y;scanf("%d%d",&x,&y);
		if(X[x]){
			add(i,X[x]);
			X[x]=0;
		}else X[x]=i;
		if(Y[y]){
			add(i,Y[y]);
			Y[y]=0;
		}else Y[y]=i;
	}
	for(int i=1;i<=n;i++)if(!vis[i])
		dfs(i);
	for(int i=1;i<=n;i++)putchar(col[i]?'b':'r');puts("");
	return 0;
}
