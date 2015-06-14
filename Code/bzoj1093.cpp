#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=100001;
int n,m;
LL mo;
vector<int>G[maxn],Ge[maxn];
int dfn[maxn],low[maxn],tot;
stack<int>S;
bool ins[maxn];
int bel[maxn],bsize,siz[maxn];
void tarjan(int u){
	S.push(u);dfn[u]=low[u]=++tot;ins[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(ins[v])low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		int v;bsize++;
		do{
			v=S.top();
			S.pop();
			ins[v]=0;
			bel[v]=bsize;
			siz[bsize]++;
		}while(u!=v);	
	}
}
set<pair<int,int> >SS;
int f[maxn];
LL g[maxn];
int vis[maxn];
LL ans1,ans2;
void dfs(int u){
	if(vis[u])return;
	vis[u]=1;
	f[u]=siz[u];g[u]=1;
	for(int i=0;i<Ge[u].size();i++){
		int v=Ge[u][i];
		dfs(v);
		if(f[u]<f[v]+siz[u])
			f[u]=f[v]+siz[u],g[u]=0;
		if(f[u]==f[v]+siz[u])
			g[u]=(g[u]+g[v])%mo;
	}
	if(f[u]>ans1)
		ans1=f[u],ans2=0;
	if(f[u]==ans1)
		ans2=(ans2+g[u])%mo;
}
int main(){
	scanf("%d%d%lld",&n,&m,&mo);
	for(int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
	}for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
	for(int i=1;i<=n;i++)
	for(int j=0;j<G[i].size();j++){
		int u=bel[i],v=bel[G[i][j]];
		if(u!=v&&!SS.count(make_pair(u,v))){
			Ge[u].push_back(v);
		//	cerr<<u<<" "<<v<<endl;
			SS.insert(make_pair(u,v));
		}
	}for(int i=1;i<=bsize;i++)dfs(i);
	cout<<ans1<<endl<<ans2<<endl;
	return 0;
}
