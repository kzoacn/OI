#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,m,cnt,T;
vector<int>G[maxn];
int vis[maxn];
int iscut[maxn],dfn[maxn],low[maxn],tot;
void dfs(int u,int fa){
	low[u]=dfn[u]=++tot;
	int ch=0;
	for(int v,i=0;i<G[u].size();i++){
		if(!dfn[v=G[u][i]]){
			ch++;
			dfs(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u])iscut[u]=1;
		}else{
			if(v!=fa)
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(!fa&&ch==1)iscut[u]=0;
}
int main(){
//	freopen("cut.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])
		dfs(i,0);
	for(int i=1;i<=n;i++)if(iscut[i])printf("%d\n",i);
	return 0;
}
