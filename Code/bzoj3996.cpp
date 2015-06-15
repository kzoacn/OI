#include<bits/stdc++.h>
using namespace std;
const int maxn=510;
struct edge{int u,v,cap,flow;};
vector<edge>edges;
vector<int>G[maxn];
int s,t,n;
int cur[maxn],d[maxn];
void add(int u,int v,int cap){
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
int B[maxn][maxn],C[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	scanf("%d",&B[i][j]);
	for(int i=1;i<=n;i++)
	scanf("%d",&C[i]);
	s=0;t=n+1;
	for(int i=1;i<=n;i++)
		add(s,i,accumulate(B[i]+1,B[i]+1+n,0));
	for(int i=1;i<=n;i++)
		add(i,t,C[i]);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		add(i,j,B[j][i]);
	cout<<accumulate(&B[1][1],(&B[n][n])+1,0)-dinic()<<endl;
	return 0;
}
