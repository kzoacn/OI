#include<bits/stdc++.h>
using namespace std;
const int maxn=500001;
struct sgt{
	#define lson i<<1,l,(l+r)/2
	#define rson i<<1|1,(l+r)/2+1,r
	#define ls i<<1
	#define rs i<<1|1
	struct node{
		int lazy,sum;
		node(){lazy=-1;}
	}t[maxn<<2];
	void rz(int i){
		t[i].sum=t[ls].sum+t[rs].sum;
	}
	void pd(int i,int l,int r){
		if(t[i].lazy!=-1){
			t[ls].sum=0;
			t[rs].sum=0;
			t[ls].lazy=0;
			t[rs].lazy=0;
			t[i].lazy=-1;
		}
	}
	void build(int i,int l,int r){
		if(l==r){t[i].sum=1;return;}
		build(lson);build(rson);rz(i);
	}
	void set0(int i,int l,int r,int l0,int r0){
		if(l0>r0)swap(l0,r0);
		if(l0<=l&&r0>=r){t[i].sum=t[i].lazy=0;return;}pd(i,l,r);
		if(l0<=(l+r)/2)set0(lson,l0,r0);
		if(r0>(l+r)/2)set0(rson,l0,r0);
		rz(i);
	}
	int get(int i,int l,int r,int ps){
		if(l==r)return t[i].sum;pd(i,l,r);
		if(ps<=(l+r)/2)return get(lson,ps);
		else return get(rson,ps);	
	}
}T;
vector<int>G[maxn];
int fa[maxn],top[maxn],siz[maxn],son[maxn],mp[maxn],z,dep[maxn],n,m,a,b;
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
	top[u]=tp;mp[u]=++z;
	if(son[u])build(son[u],tp);
	for(int v,i=0;i<G[u].size();i++)if((v=G[u][i])!=son[u]&&v!=fa[u])build(v,v);
}
int dis(int u,int v){
	int ans=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		ans+=dep[u]-dep[fa[top[u]]];
		 u=fa[top[u]];	
	}if(dep[u]>dep[v])swap(u,v);
	return ans+dep[v]-dep[u];
}
void set0(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		T.set0(1,1,n,mp[top[u]],mp[u]);
		u=fa[top[u]];	
	}if(dep[u]>dep[v])swap(u,v);
	T.set0(1,1,n,mp[u],mp[v]);
}
int main(){
	scanf("%d%d%d",&n,&m,&a);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}dfs(1);build(1,1);T.build(1,1,n);
	long long ans=0;
	while(m--){
		scanf("%d",&b);
		if(!T.get(1,1,n,mp[b]))continue;
		int res=dis(a,b);
		set0(a,b);
		//cerr<<a<<"->"<<b<<" "<<res<<endl;
		a=b;ans+=res;
	}cout<<ans<<endl;
	return 0;
}
