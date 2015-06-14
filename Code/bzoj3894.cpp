#include<bits/stdc++.h>
using namespace std;
const int maxn=500*500+5;
struct edge{int u,v,cap,flow;};
vector<edge>edges;
vector<int>G[maxn];
int s,t;
int cur[maxn],d[maxn];
void add(int u,int v,int cap){
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
	}if(!flow)d[u]=-1;
	return flow;
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
int n,m;
int mp[501][501],a[501][501];
const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};
int main(){
	s=0;t=maxn-1;
	long long sum=0;
	scanf("%d%d",&n,&m);int tot=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)mp[i][j]=++tot;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		int x;scanf("%d",&x);
		add(s,mp[i][j],x);sum+=x;
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		int x;scanf("%d",&x);
		add(mp[i][j],t,x);sum+=x;
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		add(s,++tot,a[i][j]);sum+=a[i][j];
		add(tot,mp[i][j],INT_MAX);
		for(int k=0;k<4;k++){
			int x=i+dx[k],y=j+dy[k];
			if(x<1||x>n||y<1||y>m)continue;
			add(tot,mp[x][y],INT_MAX);
		}
	}for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		add(++tot,t,a[i][j]);sum+=a[i][j];
		add(mp[i][j],tot,INT_MAX);
		for(int k=0;k<4;k++){
			int x=i+dx[k],y=j+dy[k];
			if(x<1||x>n||y<1||y>m)continue;
			add(mp[x][y],tot,INT_MAX);
		}
	}
	cout<<sum-dinic()<<endl;
	return 0;
}
