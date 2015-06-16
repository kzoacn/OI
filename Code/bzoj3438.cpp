#include<bits/stdc++.h>
using namespace std;
const int maxn=3050;
typedef long long LL;
struct edge{int u,v;LL cap,flow;};
vector<edge>edges;
vector<int>G[maxn];
int s,t;
int cur[maxn],d[maxn];
void add(int u,int v,LL cap){
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
LL dfs(int u,LL a){
	if(u==t||!a)return a;
	LL flow=0,f;
	for(int &i=cur[u];i<G[u].size();i++){
		edge e=edges[G[u][i]];
		if(d[e.v]==d[u]+1&&(f=dfs(e.v,min(a,e.cap-e.flow)))>0){
			edges[G[u][i]].flow+=f;
			edges[G[u][i]^1].flow-=f;
			flow+=f;a-=f;if(!a)break;
		}
	}return flow;
}
LL dinic(){
	LL flow=0,x;
	while(bfs()){
		memset(cur,0,sizeof cur);
		while(x=dfs(s,1e16)){
			flow+=x;
			memset(cur,0,sizeof cur);
		}
	}return flow;
}
int a[maxn],b[maxn],n,m,z;
int main(){
	freopen("bzoj3438.in","r",stdin);
	scanf("%d",&n);LL sum=0;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),sum+=a[i];
	for(int i=1;i<=n;i++)scanf("%d",&b[i]),sum+=b[i];
	scanf("%d",&m);
	s=0;t=m*2+n+1;
	for(int i=1;i<=n;i++)
		add(s,i,a[i]),add(i,t,b[i]);
	z=n;
	while(m--){
		int k;scanf("%d",&k);
		int c1,c2;scanf("%d%d",&c1,&c2);
		sum+=c1;sum+=c2;
		add(s,z+1,c1);
		add(z+2,t,c2);
		for(int i=1;i<=k;i++){
			int x;scanf("%d",&x);
			add(z+1,x,1e14);
			add(x,z+2,1e14);
		}z+=2;
	}
	
	cout<<sum-dinic()<<endl;
	return 0;
}
