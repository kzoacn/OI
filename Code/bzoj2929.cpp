#include<bits/stdc++.h>
using namespace std;
#define pb push_back
struct edge{
	int u,v,c,f;
};
vector<edge>E;
vector<int>G[201];
int n;
void add(int u,int v,int c){
	E.pb((edge){u,v,c,0});
	G[u].push_back(E.size()-1);
	E.pb((edge){v,u,0,0});
	G[v].pb(E.size()-1);
}
int cur[201],s,t,d[201];
bool bfs(){
	static int vis[201];
	memset(vis,0,sizeof vis);
	queue<int>q;q.push(s);vis[s]=1;d[s]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<G[u].size();i++){
			edge e=E[G[u][i]];if(e.c==e.f||vis[e.v])continue;
			d[e.v]=d[u]+1;q.push(e.v);vis[e.v]=1;
		}
	}return vis[t];
}
int dfs(int u,int a){
	if(u==t||!a)return a;
	int f=0,fl=0;
	for(int &i=cur[u];i<G[u].size();i++){
		edge e=E[G[u][i]];
		if(d[e.v]==d[u]+1&&(f=dfs(e.v,min(a,e.c-e.f)))>0){
			fl+=f;a-=f;
			E[G[u][i]].f+=f;
			E[G[u][i]^1].f-=f;
			if(!a)break;
		}
	}if(!fl)d[u]=-1;
	return fl;
}
int dinic(){
	int f=0,x;
	while(bfs()){
		memset(cur,0,sizeof cur);
		while(x=dfs(s,1e9))
			f+=x,memset(cur,0,sizeof cur);
	}return f;
}
int main(){
	scanf("%d",&n);
	s=1;t=n;
	for(int i=1;i<n;i++){
		int m;scanf("%d",&m);
		while(m--){
			int v;scanf("%d",&v);
			add(i,v,(v==n||i==1)?1:233);
		}
	}cout<<dinic()<<endl;
	return 0;
}
