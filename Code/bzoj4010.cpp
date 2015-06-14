#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int maxn=1e5+5;
int n,m,_,in[maxn];
vector<pair<int,int> >v;
vector<int>anss;
vector<int>G[maxn];
void add(int u,int v){
	G[u].push_back(v);
}
int ins[maxn],vis[maxn];
bool dfs1(int u){
	ins[u]=1;vis[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(ins[v])return 1;
		if(vis[v])continue;
		if(dfs1(v))return 1;
	}ins[u]=0;
	return 0;
}
int tr[maxn],f[maxn];
void dfs(int u){
	if(tr[u])return;
	tr[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(!tr[v]){
			dfs(v);
			tr[u]+=tr[v];
		}else f[u]+=f[v];
	}tr[]
}
void solve(){
	scanf("%d%d",&n,&m);
	v.clear();anss.clear();
	memset(vis,0,sizeof vis);
	for(int i=1;i<=n;i++)G[i].clear(),in[i]=0;
	for(int i=0;i<m;i++){
		int x,y;scanf("%d%d",&x,&y);
		v.push_back(make_pair(x,y));
	}sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for(int i=0;i<v.size();i++)
		add(v[i].y,v[i].x);
	memset(f,0,sizeof f);
	memset(tr,0,sizeof tr);
	for(int i=1;i<=n;i++)dfs(i);
	
}
int main(){
	scanf("%d",&_);
	while(_--)solve();
	return 0;
}
