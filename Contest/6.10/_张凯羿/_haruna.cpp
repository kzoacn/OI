#include<set>
#include<map>
#include<cstdio>
#include<vector>
#include<cctype>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=50010;
template<typename T>
T in(){
	T r=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r*f;
}
int n,m;
int a[maxn];
vector<int>G[maxn];
namespace BF{
	int T,fa[maxn],dep[maxn];
	void dfs(int u){
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(fa[u]==v)continue;
			dep[v]=dep[u]+1;fa[v]=u;
			dfs(v);
		}
	}
	int vis[maxn];
	int mex(int u,int v){
		T++;
		if(dep[u]<dep[v])swap(u,v);
		while(dep[u]>dep[v])
			vis[a[u]]=T,u=fa[u];
		while(u!=v)
			vis[a[u]]=T,vis[a[v]]=T,u=fa[u],v=fa[v];
		vis[a[u]]=T;
		for(int i=0;i<=n+1;i++)if(vis[i]!=T)return i;
	}	
	void solve(){
		for(int i=1;i<=n;i++)a[i]=in<int>();
		for(int i=1;i<n;i++){
			int u=in<int>(),v=in<int>();
			G[u].push_back(v);
			G[v].push_back(u);			
		}dfs(1);
		while(m--){
			int ty=in<int>();
			if(ty==0){
				int u=in<int>(),x=in<int>();
				a[u]=x;
			}else{
				int u=in<int>(),v=in<int>();
				printf("%d\n",mex(u,v));
			}
		}		
	}
}
struct node{
	multiset<int>S;
	int l,r,bud;
}t[maxn*2];
int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn],mp[maxn],rmp[maxn],z;
void dfs(int u){
	siz[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(fa[u]==v)continue;
		dep[v]=dep[u]+1;fa[v]=u;
		dfs(v);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])son[u]=v;
	}
}
void build(int u,int tp){
	mp[u]=++z;rmp[z]=u;top[u]=tp;
	if(son[u])build(son[u],tp);
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v!=fa[u]&&v!=son[u])build(v,v);
	}
}
int tot=0;
int buildT(int l,int r){
	int x=++tot;
	for(int i=l;i<=r;i++)t[x].S.insert(a[rmp[i]]);
	if(l==r)return x;
	t[x].l=buildT(l,(l+r)/2);
	t[x].r=buildT((l+r)/2+1,r);
	return x;
}
#define lson t[i].l,l,(l+r)/2
#define rson t[i].r,(l+r)/2+1,r
void C(int i,int l,int r,int ps,int x){
	t[i].S.erase(t[i].S.find(a[rmp[ps]]));
	t[i].S.insert(x);
	if(l==r)return void(a[rmp[ps]]=x);
	if(ps<=(l+r)/2)C(lson,ps,x);
	else C(rson,ps,x);
}
bool Q(int i,int l,int r,int l0,int r0,int x){
	if(l0>r0)swap(l0,r0);
	if(l0<=l&&r0>=r)return t[i].S.count(x);
	if(l0<=(l+r)/2)if(Q(lson,l0,r0,x))return 1;
	if(r0>(l+r)/2)if(Q(rson,l0,r0,x))return 1;
	return 0;
}
bool exist(int u,int v,int d){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		if(Q(1,1,n,mp[u],mp[top[u]],d))return 1;	
		u=fa[top[u]];
	}if(Q(1,1,n,mp[u],mp[v],d))return 1;	
	return false;
}
int Q(int u,int v){
	for(int i=0;i<=n+1;i++)
		if(!exist(u,v,i))return i;	
}
void solve(){
	for(int i=1;i<=n;i++)a[i]=in<int>();
	for(int i=1;i<n;i++){
		int u=in<int>(),v=in<int>();
		G[u].push_back(v);
		G[v].push_back(u);
	}dfs(1);build(1,1);
	buildT(1,n);
	map<pair<int,int>,int>rem;
	while(m--){
		int ty=in<int>();
		if(ty==0){
			int ps=in<int>(),x=in<int>();
			C(1,1,n,mp[ps],x);
		}else{
			int u=in<int>(),v=in<int>();
			if(u>v)swap(u,v);
			if(rem.count(make_pair(u,v)))printf("%d\n",rem[make_pair(u,v)]);else printf("%d\n",rem[make_pair(u,v)]=Q(u,v));
		}
	}	
}
int main(){
	freopen("haruna.in","r",stdin);
	n=in<int>();m=in<int>();
	if(n<=100&&m<=100)
		BF::solve();
	else solve();
	return 0;
}
