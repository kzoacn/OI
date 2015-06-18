#include<bits/stdc++.h>
using namespace std;
const int maxn=1000001;
int n,m;
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
int fa[maxn],top[maxn],dep[maxn],mp[maxn],z;
vector<vector<int> >G;
vector<int>son,siz;
long long anss[8];
void dfs(int u){
	siz[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==fa[u])continue;
		fa[v]=u;dep[v]=dep[u]+1;
		dfs(v);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])son[u]=v;
	}
}
void build(int u,int tp){
	mp[u]=++z;top[u]=tp;
	if(son[u])build(son[u],tp);
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v!=fa[u]&&v!=son[u])build(v,v);
	}
}
struct node{
	int all,laz;
	int l,r;
	void rz();
	void pd();
}t[maxn*2];
void node::rz(){
	all=t[l].all==t[r].all?t[l].all:-1;
}
void node::pd(){
	if(!laz)return;
	t[l].all=t[l].laz=laz;
	t[r].all=t[r].laz=laz;
	laz=0;
}
int tot=0;
int buildT(int l,int r){
	int x=++tot;
	if(l==r)return x;
	t[x].l=buildT(l,(l+r)/2);
	t[x].r=buildT((l+r)/2+1,r);	
	return x;
}
void Q(int i,int l,int r,int l0,int r0,int c){
	if(l0>r0)return;
	if(l==r){
		if(t[i].all==c)return void(t[i].laz=c);
		anss[c]+=r-l+1;
		t[i].all=t[i].laz=c;
		return;		
	}
	if(l0<=l&&r0>=r&&t[i].all!=-1){
		if(t[i].all==c)return void(t[i].laz=c);
		anss[c]+=r-l+1;
		t[i].all=t[i].laz=c;
		return;
	}t[i].pd();
	if(l0<=(l+r)/2)Q(t[i].l,l,(l+r)/2,l0,r0,c);
	if(r0>(l+r)/2)Q(t[i].r,(l+r)/2+1,r,l0,r0,c);
	t[i].rz();
}
void Q(int u,int v,int c){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		Q(1,1,n,mp[top[u]],mp[u],c);
		u=fa[top[u]];
	}if(mp[u]>mp[v])swap(v,u);
	Q(1,1,n,mp[u]+1,mp[v],c);
}
int main(){
//	freopen("bzoj1759.in","r",stdin);
	n=in();
	G.resize(n+1);
	son.resize(n+1);
	siz.resize(n+1);
	for(int i=1;i<n;i++){
		int u=in(),v=in();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	int root=1;
	dfs(root);
	siz.clear();
	build(root,root);
	son.clear();
	G.clear();
	
	buildT(1,n);
	
	int m=in();
	while(m--){
		int u=in(),v=in(),c=in();	
		Q(u,v,c);
	}
	for(int i=1;i<=7;i++)
		printf("%lld\n",anss[i]);
	return 0;
}
