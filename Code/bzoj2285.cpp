#include<bits/stdc++.h>
using namespace std;
const double eps=1e-5;
const double inf=1e9;
int dcmp(double x){return (x>1e-6)-(x<-1e-6);}
namespace MinCut{
	int s=0,t=176;
	struct edge{
		int u,v;
		double cap,flow;
	};
	vector<edge>edges;
	vector<int>G[177];
	void add(int u,int v,double cap){
		edges.push_back((edge){u,v,cap,0});
		G[u].push_back(edges.size()-1);
		edges.push_back((edge){v,u,0,0});
		G[v].push_back(edges.size()-1);
	}
	int d[177];
	bool bfs(){
		static int vis[177];
		memset(vis,0,sizeof vis);
		queue<int>q;q.push(s);vis[s]=1;
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=0;i<G[u].size();i++){
				edge e=edges[G[u][i]];
				if(!vis[e.v]&&e.cap-e.flow>eps){
					vis[e.v]=1;d[e.v]=d[u]+1;
					q.push(e.v);
				}
			}
		}return vis[t];
	}
	int cur[177];
	double dfs(int u,double a){
		if(u==t||a<eps)return a;
		double flow=0,f;
		for(int &i=cur[u];i<G[u].size();i++){
			edge e=edges[G[u][i]];
			if(d[e.v]==d[u]+1&&(f=dfs(e.v,min(a,e.cap-e.flow)))>eps){
				flow+=f;a-=f;
				edges[G[u][i]].flow+=f;
				edges[G[u][i]^1].flow-=f;
				if(!dcmp(a))break;
			}
		}if(!dcmp(flow))d[u]=-1;
		return flow;
	}
	double dinic(){
		double flow=0;
		while(bfs()){
			double x;
			memset(cur,0,sizeof cur);
			while((x=dfs(s,1e9))>eps)flow+=x;
		}return flow;
	}
	
}
struct edge{
	int u,v;
	double w,a,b;
};
int n,m,n1,m1;
vector<edge>edges;
vector<int>G[707];
bool vis[707];
double d[707];
double dfs(int u){
	if(vis[u])return d[u];
	vis[u]=1;d[u]=1e9;
	for(int i=0;i<G[u].size();i++){
		edge e=edges[G[u][i]];
		d[u]=min(d[u],dfs(e.v)+e.w);
	}return d[u];
}
double calc(int x){
	double l=0,r=11;
	while(r-l>eps){
		double mid=(l+r)/2;
		for(int i=0;i<edges.size();i++)edges[i].w=edges[i].a-mid*edges[i].b;
		memset(vis,0,sizeof vis);vis[n]=1;
		if(dfs(x)>=-eps)
			l=mid;
		else r=mid;
	}return l>10.5?1e9:l;
}
double w[177];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;double a,b;
		scanf("%d%d%lf%lf",&u,&v,&a,&b);
		edges.push_back((edge){v,u,0,a,b});
		G[v].push_back(edges.size()-1);
	}
	scanf("%d%d",&m1,&n1);
 	for(int i=1;i<=n1;i++)
		w[i]=calc(i);
	for(int i=1;i<=n1;i++)if(i&1)MinCut::add(MinCut::s,i,w[i]);
	else MinCut::add(i,MinCut::t,w[i]);
	for(int i=1;i<=m1;i++){
		int u,v;scanf("%d%d",&u,&v);
		MinCut::add(u,v,inf);
	}double ans=MinCut::dinic();
	if(ans>=1e8)puts("-1");
	else printf("%.1lf\n",ans);
	return 0;
}
