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
int tot=0;
int mp[102][2];
int main(){
	int n,M;scanf("%d%d",&n,&M);
	for(int i=1;i<=n;i++)mp[i][0]=++tot,mp[i][1]=++tot;
	s=0;t=tot+1;int ss=t+1,tt=ss+1;
	add(tt,ss,M,0);
	
	for(int i=1;i<=n;i++){
		int v;scanf("%d",&v);
		add(s,mp[i][1],v,0);
		add(mp[i][0],t,v,0);
		add(ss,mp[i][0],1e9,0);
		add(mp[i][1],tt,1e9,0);
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			int v;scanf("%d",&v);if(v==-1)continue;
			add(mp[i][1],mp[j][0],1e9,v);
		}
	}
	while(spfa());
	cout<<cost<<endl;
	return 0;
}
