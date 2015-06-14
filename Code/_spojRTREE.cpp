#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
vector<int>G[maxn];
int rt,fa[maxn],n,m;
int anss[maxn],maxd[maxn],tmp[maxn];
void dfs(int u){
	for(int v,i=0;i<G[u].size();i++){
		if((v=G[u][i])!=fa[u]){
			fa[v]=u;
			dfs(v);
		}
	}
}
int vis[maxn];
int bfs(int s){
	queue<int>q;q.push(s);
	static int d[maxn];
	memset(d,-1,sizeof d);
	memset(vis,0,sizeof vis);
	d[s]=0;vis[s]=vis[fa[s]]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v,i=0;i<G[u].size();i++){
			if(!vis[v=G[u][i]]){
				d[v]=d[u]+1;
				q.push(v);
				vis[v]=1;
			}
		}
	}int ss=max_element(d+1,d+1+n)-d;
	memset(d,-1,sizeof d);memset(vis,0,sizeof vis);
	vis[fa[s]]=1;vis[ss]=1;d[ss]=0;
	q.push(ss);
		while(!q.empty()){
		int u=q.front();q.pop();
		for(int v,i=0;i<G[u].size();i++){
			if(!vis[v=G[u][i]]){
				d[v]=d[u]+1;
				q.push(v);
				vis[v]=1;
			}
		}
	}return *max_element(d+1,d+1+n);
	
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}scanf("%d",&rt);dfs(rt);
	scanf("%d",&m);
	while(m--){
		int u;scanf("%d",&u);
		vis[fa[u]]=1;
		printf("%d\n",bfs(u));
		vis[fa[u]]=0;
	}
	return 0;
}
