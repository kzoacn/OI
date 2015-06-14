#include<bits/stdc++.h>
using namespace std;
const int maxn=5150;
struct edge{int u,v,cap,flow;};
vector<edge>edges;
vector<int>G[maxn];
int s,t;
int cur[maxn],d[maxn];
void add(int u,int v,int cap){
	if(u==-1)return;
//	cerr<<u<<" "<<v<<" "<<cap<<endl;
	edges.push_back((edge){u,v,cap,0});
	G[u].push_back(edges.size()-1);
	edges.push_back((edge){v,u,0,0});
	G[v].push_back(edges.size()-1);
}
bool bfs(){
	static int vis[maxn];
	memset(vis,0,sizeof vis);vis[s]=1;
	queue<int>q;q.push(s);d[s]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<G[u].size();i++){
			edge e=edges[G[u][i]];if(vis[e.v]||e.cap==e.flow)continue;
			d[e.v]=d[u]+1;vis[e.v]=1;q.push(e.v);
		}
	}return vis[t];
}
int dfs(int u,int a){
	if(u==t||!a)return a;
	int flow=0,f;
	for(int &i=cur[u];i<G[u].size();i++){
		edge e=edges[G[u][i]];
		if(d[e.v]==d[u]+1&&(f=dfs(e.v,min(a,e.cap-e.flow)))>0){
			edges[G[u][i]].flow+=f;
			edges[G[u][i]^1].flow-=f;
			flow+=f;a-=f;if(!a)break;
		}
	}return flow;
}
int dinic(){
	int flow=0,x;
	while(bfs()){
		memset(cur,0,sizeof cur);
		while(x=dfs(s,INT_MAX)){
			flow+=x;
			memset(cur,0,sizeof cur);
		}
	}return flow;
}
int n,m,T;
int tot;
int mp[101][51];
edge E[2450];
void Add(int x){
	for(int i=1;i<=n;i++)mp[x][i]=++tot;
	for(int i=0;i<edges.size();i++)edges[i].flow=0;
	for(int i=1;i<=n;i++)add(mp[x-1][i],mp[x][i],1e9);
	for(int i=0;i<m;i++){
		edge e=E[i];
		add(mp[x-1][e.u],mp[x][e.v],e.cap);
	}add(mp[x][n],t,T);
}
int main(){
	s=maxn-2;t=maxn-1;
	scanf("%d%d%d",&n,&m,&T);
	add(s,0,T);
	if(n==1){puts("0");return 0;}
	for(int i=2;i<=n;i++)mp[0][i]=-1;
	for(int i=0;i<m;i++)
		scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].cap);
	for(int i=1;i<=n+T;i++){
		Add(i);
		if(dinic()==T){printf("%d\n",i);return 0;}
	}puts("-1");
	return 0;
}
