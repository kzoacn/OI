#include<bits/stdc++.h>
using namespace std;
const int maxn=233;
int s,t;
struct edge{int u,v,ca,fl,co;};
vector<edge>E;
vector<int>G[maxn];
void add(int u,int v,int ca,int co){
//	cerr<<u<<" "<<v<<" "<<ca<<" "<<co<<endl; 
	E.push_back((edge){u,v,ca,0,co});
	G[u].push_back(E.size()-1);
	E.push_back((edge){v,u,0,0,-co});
	G[v].push_back(E.size()-1);
}
int cost,flow=0;
bool spfa(){
	static int vis[maxn],d[maxn],a[maxn],pre[maxn];
	memset(d,0xaf,sizeof d);int B=d[0];a[s]=INT_MAX;
	queue<int>q;q.push(s);vis[s]=1;d[s]=0;	
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=0;i<G[u].size();i++){
			edge e=E[G[u][i]];
			if(e.ca==e.fl||d[e.v]>=d[u]+e.co)continue;
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
	int n;scanf("%d",&n);int M=0;
	s=0;t=n+1;int ss=t+1,tt=s+1;
	for(int i=1;i<=n;i++){
		int m;scanf("%d",&m);M+=m;
		for(int j=1;j<=m;j++){
			int v;scanf("%d",&v);
			add(i,v,1,1);
			add(i,v,1e9,0);
		}
		add(ss,i,1e9,0);
		add(i,t,1e9,0);
	}add(s,ss,0,0);
	
	for(int i=1;i<=23333;i++){
		E[E.size()-2].ca++;
		spfa();
		if(cost==M){printf("%d\n",i);return 0;}
	}
	return 0;
}
