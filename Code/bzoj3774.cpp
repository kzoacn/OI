#include<bits/stdc++.h>
using namespace std;
const int maxn=5050;
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
int a[501][501],n,ans,tot,m;
int b[501][501]; 
int mp[501][501][2];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",&b[i][j]),ans+=b[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)mp[i][j][0]=++tot,mp[i][j][1]=++tot;
	s=0;t=tot+1;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		if((i+j)%2){
			add(s,mp[i][j][0],a[i][j]);
			add(mp[i][j][0],mp[i][j][1],b[i][j]);
		}else{
			add(mp[i][j][0],t,a[i][j]);
			add(mp[i][j][1],mp[i][j][0],b[i][j]);
		}
		const int dx[4]={0,0,1,-1};
		const int dy[4]={1,-1,0,0};
		for(int k=0;k<4;k++){
			int x=i+dx[k],y=j+dy[k];
			if(x<1||y<1||x>n||y>m)continue;
			if((i+j)%2)add(mp[i][j][1],mp[x][y][0],1e9);
			else add(mp[x][y][0],mp[i][j][1],1e9);
		}
	}cout<<ans-dinic()<<endl;
	return 0;
}
