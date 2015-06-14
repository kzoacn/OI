#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int siz[maxn],son[maxn],top[maxn],fa[maxn],dep[maxn],mp[maxn],rmp[maxn],z;
int lef[maxn],rig[maxn],tot;
int rt,n,m,a[maxn];
vector<int>G[maxn];
struct sgt{
	struct node{
		int mn,lz;
		node(){mn=INT_MAX;lz=INT_MIN;}
		node(int mn,int lz):mn(mn),lz(lz){}
		node operator+(const node &rs){return node(min(mn,rs.mn),INT_MIN);}	
	}t[maxn<<2];
	#define lson i<<1,l,(l+r)/2
	#define rson i<<1|1,(l+r)/2+1,r
	#define ls i<<1
	#define rs i<<1|1
	void build(int i,int l,int r){
		if(l==r){t[i]=node(a[rmp[l]],INT_MIN);return;}
		build(lson);build(rson);t[i]=t[ls]+t[rs];
	}
	void pd(int i){
		if(t[i].lz!=INT_MIN){
			t[ls].mn=t[ls].lz=t[rs].mn=t[rs].lz=t[i].lz;
			t[i].lz=INT_MIN;
		}
	}
	void Cov(int i,int l,int r,int l0,int r0,int d){
		if(l0>r0)swap(l0,r0);
		if(l0<=l&&r0>=r){
			t[i].mn=t[i].lz=d;
			return ;
		}pd(i);
		if(l0<=(l+r)/2)Cov(lson,l0,r0,d);
		if(r0>(l+r)/2)Cov(rson,l0,r0,d);
		t[i]=t[ls]+t[rs];
	}
	int Qmin(int i,int l,int r,int l0,int r0){
		if(l0>r0)swap(l0,r0);
		if(l0<=l&&r0>=r)return t[i].mn;pd(i);
		int ans=INT_MAX;
		if(l0<=(l+r)/2)ans=min(ans,Qmin(lson,l0,r0));
		if(r0>(l+r)/2)ans=min(ans,Qmin(rson,l0,r0));
		return ans;
	}
}T;
void dfs(int u){
	siz[u]=1;
	for(int v,i=0;i<G[u].size();i++){
		if((v=G[u][i])==fa[u])continue;
		fa[v]=u;dep[v]=dep[u]+1;
		dfs(v);	
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])son[u]=v;
	}
}
void build(int u,int tp){
	top[u]=tp;mp[u]=++z;lef[u]=++tot;rmp[z]=u;
	if(son[u])build(son[u],tp);
	for(int v,i=0;i<G[u].size();i++)if((v=G[u][i])!=son[u]&&v!=fa[u])
	build(v,v);rig[u]=tot;
}
int lca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		u=fa[top[u]];
	}return dep[u]<dep[v]?u:v;
}
int dis(int u,int v){
	int ans=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		ans+=dep[u]-dep[top[u]]+1;
		u=fa[top[u]];
	}if(dep[u]>dep[v])swap(u,v);
	return ans+dep[v]-dep[u];
}
void Cov(int u,int v,int d){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		T.Cov(1,1,n,mp[u],mp[top[u]],d);
		u=fa[top[u]];
	}if(mp[u]>mp[v])swap(u,v);
	T.Cov(1,1,n,mp[u],mp[v],d);
}
int Qmin(int x){
	if(x==rt)return T.Qmin(1,1,n,1,n);
	int LCA=lca(x,rt);
	if(LCA!=x){
		return T.Qmin(1,1,n,lef[x],rig[x]);
	}else{
		int d=dis(x,rt);
		int u=rt;d--;
		while(dep[top[u]]>dep[x]+1)d-=dep[u]-dep[top[u]]+1,u=fa[top[u]];
		u=rmp[mp[u]-d];
		int ans=INT_MAX;
		if(1<=lef[u]-1)ans=min(ans,T.Qmin(1,1,n,1,lef[u]-1));
		if(rig[u]+1<=n)ans=min(ans,T.Qmin(1,1,n,rig[u]+1,n));
		return ans;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	dfs(1);build(1,1);
	T.build(1,1,n);
	scanf("%d",&rt);
	while(m--){
		int op;scanf("%d",&op);
		if(op==1)scanf("%d",&rt);else
		if(op==2){
			int u,v,d;scanf("%d%d%d",&u,&v,&d);
			Cov(u,v,d);
		}else
		if(op==3){
			int x;scanf("%d",&x);
			printf("%d\n",Qmin(x));
		}
	}
	return 0;
}
