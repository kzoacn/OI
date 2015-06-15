#include<bits/stdc++.h>
using namespace std;
const int maxn=55;
const double eps=1e-5;
int n,m;
int A[maxn][maxn];
int B[maxn][maxn];
int C[maxn][maxn];
struct edge{
	int u,v;
	double cap,flow;
};
vector<edge>edges;
vector<int>G[maxn*maxn];
int d[maxn*maxn];
int s,t;
int dcmp(double x){return (x>eps)-(x<-eps);}
void add(int u,int v,double cap){
//	cerr<<u<<" "<<v<<" "<<cap<<endl;
	edges.push_back((edge){u,v,cap,0});
	G[u].push_back(edges.size()-1);
	edges.push_back((edge){v,u,0,0});
	G[v].push_back(edges.size()-1);
}
bool bfs(){
	static int vis[maxn*maxn];
	memset(vis,0,sizeof vis);
	queue<int>q;q.push(s);vis[s]=1;d[s]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<G[u].size();i++){
			edge e=edges[G[u][i]];
			if(vis[e.v]||!dcmp(e.cap-e.flow))continue;
			vis[e.v]=1;d[e.v]=d[u]+1;q.push(e.v);
		}
	}return vis[t];
}
int cur[maxn*maxn];
double dfs(int x,double a){
	if(x==t||!dcmp(a))return a;
	double flow=0,f;
	for(int &i=cur[x];i<G[x].size();i++){
		edge e=edges[G[x][i]];
		if(d[e.v]==d[x]+1&&(f=dfs(e.v,min(a,e.cap-e.flow)))>eps){
			flow+=f;
			a-=f;
			edges[G[x][i]].flow+=f;
			edges[G[x][i]^1].flow-=f;
			if(!dcmp(a))break;
		}
	}if(!dcmp(flow))d[x]=-1;
	return flow;
}
double dinic(){
	double flow=0,x;
	while(bfs()){
		memset(cur,0,sizeof cur);
		while(dcmp(x=dfs(s,1e9))){
			flow+=x;
			memset(cur,0,sizeof cur);
		}
	}return flow;
}
int mp[51][51],tot;
void make(double x){
	s=0;t=maxn*maxn-1;int tt=t-1;
	edges.clear();
	for(int i=0;i<maxn*maxn;i++)G[i].clear();
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
		add(s,mp[i][j],A[i][j]);
	for(int i=1;i<=n+1;i++)
	for(int j=1;j<=m;j++){
		int u=i!=1?mp[i-1][j]:tt;
		int v=i!=n+1?mp[i][j]:tt;
		double w=x*B[i-1][j];
		add(u,v,w);add(v,u,w);
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m+1;j++){
		int u=j!=1?mp[i][j-1]:tt;
		int v=j!=m+1?mp[i][j]:tt;
		double w=x*C[i][j-1];
		add(u,v,w);add(v,u,w);
	}add(tt,t,1e9);

}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	scanf("%d",&A[i][j]);
	for(int i=0;i<=n;i++)
	for(int j=1;j<=m;j++)
	scanf("%d",&B[i][j]);
	for(int i=1;i<=n;i++)
	for(int j=0;j<=m;j++)
	scanf("%d",&C[i][j]);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
		mp[i][j]=++tot;
	double sum=accumulate(&A[0][0],(&A[n][m])+1,0.0);
	double l=0,r=250000;
	//!!!
//	r=2;

	while(dcmp(r-l)){
		double mid=(l+r)/2;

		//!!!
		//mid=3;

		make(mid);
		double mf=dinic();
		if(sum-mf>0)
			l=mid;
		else r=mid;
	}printf("%.3lf\n",l);
	return 0;
}
