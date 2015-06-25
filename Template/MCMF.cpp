#include<bits/stdc++.h>
using namespace std;
const int maxn=233;
int s,t;
struct edge{int u,v,ca,fl,co;};
vector<edge>E;
vector<int>G[maxn];
void add(int u,int v,int ca,int co){
	E.push_back((edge){u,v,ca,0,co});
	G[u].push_back(E.size()-1);
	E.push_back((edge){v,u,0,0,-co});
	G[v].push_back(E.size()-1);
}
int cost,flow=0;
bool spfa(){
	static int vis[maxn],d[maxn],a[maxn],pre[maxn];
	memset(d,0x7f,sizeof d);int B=d[0];a[s]=INT_MAX;
	queue<int>q;q.push(s);vis[s]=1;d[s]=0;	
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=0;i<G[u].size();i++){
			edge e=E[G[u][i]];
			if(e.ca==e.fl||d[e.v]<=d[u]+e.co)continue;
			a[e.v]=min(e.ca-e.fl,a[u]);pre[e.v]=G[u][i];
			d[e.v]=d[u]+e.co;if(!vis[e.v])q.push(e.v),vis[e.v]=1;
		}	
	}
	if(d[t]==B)return false;
	flow+=a[t];
	cost+=a[t]*d[t];
	int u=t;
	while(u!=s){
		E[pre[u]].fl+=a[t];
		E[pre[u]^1].fl-=a[t];
		u=E[pre[u]].u;
	}return true;
}
int main(){
	int n;scanf("%d",&n);
	s=0;t=n+1;
	for(int i=1;i<=n;i++){
		int m;scanf("%d",&m);
		for(int j=1;j<=m;j++){
			int v,z;scanf("%d%d",&v,&z);
			add(s,v,1,z);
			add(i,v,1e9,z);
		}add(i,t,m,0);
		if(i!=1)add(i,1,1e9,0);
	}while(spfa());
	cout<<cost<<endl;
	return 0;
}
