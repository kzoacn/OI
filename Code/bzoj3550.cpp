#include<bits/stdc++.h>
using namespace std;
const int maxn=610;
struct edge{
	int u,v,cap,flow,cost;
};
vector<edge>edges;
vector<int>G[maxn];
void add(int u,int v,int cap,int cost){
	edges.push_back((edge){u,v,cap,0,cost});
	G[u].push_back(edges.size()-1);
	edges.push_back((edge){v,u,0,0,-cost});
	G[v].push_back(edges.size()-1);
}
int d[maxn],vis[maxn],pre[maxn],a[maxn];
int s,t,flow,cost,n,k;
bool spfa(){
	memset(d,0xaf,sizeof d);int duang=d[0];
	queue<int>q;q.push(s);d[s]=0;a[s]=1e9;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=0;i<G[u].size();i++){
			edge e=edges[G[u][i]];
			if(e.cap==e.flow)continue;
			if(d[e.v]<d[u]+e.cost){
				d[e.v]=d[u]+e.cost;
				a[e.v]=min(e.cap-e.flow,a[u]);
				pre[e.v]=G[u][i];
				if(!vis[e.v])q.push(e.v),vis[e.v]=1;
			}
		}
	}
	if(d[t]==duang)return false;
	flow+=a[t];
	cost+=a[t]*d[t];
	int u=t;
	while(u!=s){
		edges[pre[u]].flow+=a[t];
		edges[pre[u]^1].flow-=a[t];
		u=edges[pre[u]].u;
	}return true;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=3*n;i++)scanf("%d",&a[i]);
	s=0;t=maxn-1;int ss=t-1;int tt=ss-1;
	add(s,ss,k,0);add(tt,t,k,0);
	for(int i=1;i<2*n;i++)add(i,i+1,1e9,0);
	for(int i=1;i<=n;i++)add(ss,i,1,a[i]);
	for(int i=n+1;i<=2*n;i++)add(i-n,i,1,a[i]);
	for(int i=2*n+1;i<=3*n;i++)add(i-n,i,1,a[i]);
	for(int i=2*n+1;i<=3*n;i++)add(i,tt,1,0);
	while(spfa());
	cout<<cost<<endl;
	return 0;
} 
