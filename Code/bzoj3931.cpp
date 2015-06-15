#include<bits/stdc++.h>
using namespace std;
const int maxn=1050;
typedef long long LL;
struct edge{LL u,v;LL cap,flow;};
vector<edge>edges;
vector<LL>G[maxn];
LL s,t,n,m;
LL cur[maxn];
LL d[maxn];
void add(LL u,LL v,LL cap){
//	cerr<<u<<" "<<v<<" "<<cap<<endl;
	edges.push_back((edge){u,v,cap,0});
	G[u].push_back(edges.size()-1);
	edges.push_back((edge){v,u,0,0});
	G[v].push_back(edges.size()-1);
}
bool bfs(){
	static LL vis[maxn];
	memset(vis,0,sizeof vis);vis[s]=1;
	queue<LL>q;q.push(s);d[s]=0;
	while(!q.empty()){
		LL u=q.front();q.pop();
		for(LL i=0;i<G[u].size();i++){
			edge e=edges[G[u][i]];if(vis[e.v]||e.cap==e.flow)continue;
			d[e.v]=d[u]+1;vis[e.v]=1;q.push(e.v);
		}
	}return vis[t];
}
LL dfs(LL u,LL a){
	if(u==t||!a)return a;
	LL flow=0,f;
	for(LL &i=cur[u];i<G[u].size();i++){
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
		while(x=dfs(s,1e15)){
			flow+=x;
			memset(cur,0,sizeof cur);
		}
	}return flow;
}
namespace SP{
	struct edge{
		LL u,v;LL w;
	};
	vector<edge>E;
	vector<LL>G[maxn];
	void add(LL u,LL v,LL w){
		E.push_back((edge){u,v,w});
		G[u].push_back(E.size()-1);
		E.push_back((edge){v,u,w});
		G[v].push_back(E.size()-1);
	}
	LL d[maxn];
	void spfa(){
		static LL vis[maxn];
		memset(vis,0,sizeof vis);vis[1]=1;
		for(LL i=1;i<=n;i++)d[i]=1e15;
		d[1]=0;
		queue<LL>q;q.push(1);vis[1]=1;
		while(!q.empty()){
			LL u=q.front();q.pop();vis[u]=0;
			for(LL i=0;i<G[u].size();i++){
				edge e=E[G[u][i]];
				if(d[e.v]>d[u]+e.w){
					d[e.v]=d[u]+e.w;
					if(!vis[e.v])q.push(e.v),vis[e.v]=1;
				}
			}
		}
		for(LL i=0;i<E.size();i++){
			LL u=E[i].u,v=E[i].v;LL w=E[i].w;
			if(d[u]+w==d[v])
				::add(u*2,v*2-1,1e15);
		}
	}
}
int main(){
	freopen("bzoj3931.in","r",stdin);
	scanf("%lld%lld",&n,&m);
	for(LL i=1;i<=m;i++){
		LL u,v;LL w;scanf("%lld%lld%lld",&u,&v,&w);
		SP::add(u,v,w);
	}SP::spfa();
	s=2;t=n*2-1;
	for(LL i=1;i<=n;i++){
		LL c;
		scanf("%lld",&c);
		add(i*2-1,i*2,c);
	}
	cout<<dinic()<<endl;
	return 0;
}
