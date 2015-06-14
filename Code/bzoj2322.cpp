#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=5005;
struct edge{int u,v;LL w;};
vector<edge>edges;
vector<int>G[maxn];
int n,m,q;
LL anss[20001];
int Q[20001],vis[maxn];
bool cant[40000];
map<LL,LL>S;
LL d[maxn],base[64],bsize;
void insert(LL x){
	for(int i=63;i>=0;i--){
		if(x>>i&1){
			if(!base[i]){
				base[i]=x;
				bsize++;
				break;
			}else x^=base[i];
		}		
	}
}
LL get(LL x){
	for(int i=63;i>=0;i--)
		if(x>>i&1)x^=base[i];
	return x;
}
LL tmp;
vector<LL>path;
int tme;
void dfs(int u){
	if(!vis[u])
	path.push_back(d[u]);
	vis[u]=1;
	for(int i=0;i<G[u].size();i++){
		if(cant[G[u][i]])continue;
		edge e=edges[G[u][i]];
		if(vis[e.v]){
			insert(d[e.u]^e.w^d[e.v]);
		}else d[e.v]=e.w^d[e.u],dfs(e.v);
	}
}
void init(){
	path.clear();
}
void calc(){
	for(map<LL,LL>::iterator it=S.begin();it!=S.end();it++)
		path.push_back(it->second);
	S.clear();
	for(int i=0;i<path.size();i++){
		LL tmp=get(path[i]);
		if(!S.count(tmp))S[tmp]=path[i];
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++){
		int u,v;LL w;scanf("%d%d%lld",&u,&v,&w);
		edges.push_back((edge){u,v,w});
		G[u].push_back(edges.size()-1);
		edges.push_back((edge){v,u,w});
		G[v].push_back(edges.size()-1);
	}for(int i=1;i<=q;i++){
		int x;scanf("%d",&x);
		cant[x-1<<1]=cant[x-1<<1|1]=1;
		Q[i]=x;
	}
	for(int i=q;i>=1;i--){
		tme++;
		init();
		edge e=edges[Q[i]-1<<1];
		calc();
		anss[i]=(LL)S.size()*(1LL<<bsize)-1;
		cant[Q[i]-1<<1]=cant[Q[i]-1<<1|1]=0;
	}init();tme++;dfs(1);calc();anss[0]=(LL)S.size()*(1LL<<bsize)-1;
	for(int i=0;i<=q;i++)printf("%lld\n",anss[i]);
	return 0;
}
