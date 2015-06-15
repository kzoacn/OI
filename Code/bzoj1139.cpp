#include<bits/stdc++.h>
#define fir first
#define sec second
using namespace std;
const int maxn=201;
const int BIT=13;
typedef pair<int,int> pack;
int n,m,p,k;
int D[maxn];
struct edge{int u,v,w,s;};
vector<edge>G[maxn];
void add(int u,int v,int w,int s){
	G[u].push_back((edge){u,v,w,s});
	G[v].push_back((edge){v,u,w,s});
}
void spfa(){
	static int d[maxn][1<<BIT];
	static int vis[maxn][1<<BIT];
	memset(d,0x7f,sizeof d);int B=d[0][0];
	d[1][D[1]]=0;
	queue<pack>q;q.push(pack(1,D[1]));
	while(!q.empty()){
		int u=q.front().fir;
		int S=q.front().sec;q.pop();vis[u][S]=0;
		for(int i=0;i<G[u].size();i++){
			edge e=G[u][i];
			if((S&e.s)!=e.s)continue;
			if(d[e.v][S|D[e.v]]>d[u][S]+e.w){
				d[e.v][S|D[e.v]]=d[u][S]+e.w;
				if(!vis[e.v][S|D[e.v]])
					q.push(pack(e.v,S|D[e.v])),
					vis[e.v][S|D[e.v]]=1;
			}
		}
	}
	int ans=*min_element(d[n],d[n]+(1<<p));
	if(ans==B)puts("-1");
	else cout<<ans<<endl;
}
int main(){
	freopen("bzoj1139.in","r",stdin);
	scanf("%d%d%d%d",&n,&m,&p,&k);
	for(int i=1;i<=k;i++){
		int w,q;scanf("%d%d",&w,&q);
		int s=0;
		while(q--){
			int x;scanf("%d",&x);
			s|=1<<(x-1);
		}D[w]|=s;
	}
	while(m--){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		int q,s=0;scanf("%d",&q);
		while(q--){
			int x;scanf("%d",&x);
			s|=1<<(x-1);
		}add(u,v,w,s);
	}spfa();
	return 0;
}
