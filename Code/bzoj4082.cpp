#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int n,m;
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
struct Seg{
	int l,r;
	bool operator<(const Seg &oth)const{return r!=oth.r?r<oth.r:l<oth.l;}
}se[maxn];
int fa[maxn<<1],dep[maxn<<1],can[maxn<<1];
vector<int>G[maxn<<1];
void find(int x){
	if(dep[x])return;
	if(!fa[x]){
		dep[x]=1;
		if(x>n&&can[x]){
			fa[x]=2*n+1;
			G[2*n+1].push_back(x);
//			cerr<<2*n+1<<" "<<x<<endl;
		}return;
	}
	find(fa[x]);
	G[fa[x]].push_back(x);
//	cerr<<fa[x]<<" "<<x<<endl;
	dep[x]=dep[fa[x]]+1;
}
int son[maxn<<1],siz[maxn<<1],top[maxn<<1];
void dfs(int u){
	siz[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		dfs(v);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])son[u]=v;
	}
}
void build(int u,int tp){
	top[u]=tp;
	if(son[u])build(son[u],tp);
	for(int i=0;i<G[u].size();i++)if(G[u][i]!=son[u])
		build(G[u][i],G[u][i]);
}
set<int>S;
int lca(int x,int y){
	int ans=0;y=*S.lower_bound(y);
	if(top[y]==0||top[x]==0)return 0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int main(){
	n=in();m=in();
	for(int i=1;i<=m;i++){
		se[i].l=in();
		se[i].r=in();
		if(se[i].l>se[i].r)se[i].r+=n;
	}sort(se+1,se+1+m);
	for(int i=m;i>=1;i--){
		if(!fa[se[i].l]){ 
			for(int j=se[i].l;j<=n&&j<=se[i].r&&!fa[j];j++){
				fa[j]=se[i].r+1;can[fa[j]]=1;
				if(fa[j]>n)S.insert(fa[j]);
			}
		}
	}
	S.insert(2*n+2);
	for(int i=1;i<=n*2;i++)
		find(i);
	dfs(2*n+1);
	build(n*2+1,n*2+1);
	int ans=INT_MAX;
	for(int i=1;i<=n;i++){
		int LCA=lca(i,i+n);
		if(LCA)
		ans=min(ans,dep[i]-dep[LCA]);
	}
	if(ans==INT_MAX)puts("impossible");
	else cout<<ans<<endl;
	return 0;
}
