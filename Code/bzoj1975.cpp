#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#define pb push_back
#define mp make_pair
using namespace std;
const int maxn=5001;
int n,m;
double E;
vector<pair<int,double> >G[maxn],Ge[maxn];
double d[maxn];
struct State{
	int x;
	double g;
	bool operator<(const State &o)const{return d[x]+g>d[o.x]+o.g;}
};
void spfa(){
	for(int i=1;i<=n;i++)d[i]=2e9;d[n]=0;
	static bool vis[maxn];vis[n]=1;
	queue<int>q;q.push(n);
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int v,i=0;i<Ge[u].size();i++){
			v=Ge[u][i].first;double w=Ge[u][i].second;
			if(d[v]+1e-9>d[u]+w){
				d[v]=d[u]+w;
				if(!vis[v])q.push(v),vis[v]=1;
			}
		}
	}
}
priority_queue<State>Q;
int dcmp(double x){return (x>1e-9)-(x<1e-9);}
int main(){
	scanf("%d%d%lf",&n,&m,&E);
	for(int i=1;i<=m;i++){
		int u,v;double w;scanf("%d%d%lf",&u,&v,&w);
		G[u].pb(mp(v,w));
		Ge[v].pb(mp(u,w));
	}spfa();
	int ans=0;
	Q.push((State){1,0});
	while(!Q.empty()){
		int u=Q.top().x;double g=Q.top().g;Q.pop();
		if(u==n){if(E-(d[u]+g)>0)E-=(d[u]+g),ans++;else break;}
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i].first;double w=G[u][i].second;
			Q.push((State){v,g+w});
		}
	}printf("%d\n",ans);
	return 0;
}
