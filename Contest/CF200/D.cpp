#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+5;
vector<int>G[maxn];
int fa[maxn],top[maxn],siz[maxn],son[maxn],mp[maxn],z,dep[maxn];
int lef[maxn],rig[maxn];
int n,m;
void dfs(int u){
	siz[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v!=fa[u]){
			fa[v]=u;dep[v]=dep[u]+1;
			dfs(v);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])son[u]=v;
		}
	}
}
void build(int u,int tp){
	top[u]=tp;mp[u]=++z;lef[u]=z;
	if(son[u])build(son[u],tp);
	for(int v,i=0;i<G[u].size();i++)if((v=G[u][i])!=son[u]&&v!=fa[u])build(v,v);
	rig[u]=z;
}
struct node{
	int all;
	int l,r;
	node(){all=-1;}
	void pd();
}t[maxn*2];
void node::pd(){
	if(all==-1)return;
	t[l].all=t[r].all=all;
	all=-1;
}
int tot;
int buildT(int l,int r){
	int x=++tot;
	if(l==r)return x;
	int mid=(l+r)>>1;
	t[x].l=buildT(l,mid);
	t[x].r=buildT(mid+1,r);
	return x;
}
void C(int x,int l,int r,int l0,int r0,int d){
	if(l0>r0)swap(l0,r0);
	if(l0<=l&&r0>=r){t[x].all=d;return;}
	t[x].pd();
	int mid=(l+r)/2;
	if(l0<=mid)C(t[x].l,l,mid,l0,r0,d);
	if(r0>mid)C(t[x].r,mid+1,r,l0,r0,d);
}
int Q(int x,int l,int r,int ps){
	if(l==r)return t[x].all;
	t[x].pd();
	if(ps<=(l+r)/2)return Q(t[x].l,l,(l+r)/2,ps);
	else return Q(t[x].r,(l+r)/2+1,r,ps);
}
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
void S(int v){
	C(1,1,n,lef[v],rig[v],1);
}
void C(int v){
	while(top[v]!=1){
		C(1,1,n,mp[v],mp[top[v]],0);
		v=fa[top[v]];
	}C(1,1,n,mp[v],mp[1],0);
}
int main(){
	freopen("D.in","r",stdin);
	n=in();
	for(int i=1;i<n;i++){
		int u=in(),v=in();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	
	dfs(1);
	build(1,1);
	
	buildT(1,n);
	
	m=in();
	while(m--){
		int ty=in(),v=in();
		if(ty==1){
			S(v);
		}else
		if(ty==2){
			C(v);
		}else puts(Q(1,1,n,mp[v])==1?"1":"0");
	}
	
	return 0;
}
