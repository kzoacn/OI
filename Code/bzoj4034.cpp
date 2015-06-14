#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=100005; 
int n,m;
int getn(){
	int res=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
vector<int>G[maxn];
int a[maxn],fa[maxn],siz[maxn],son[maxn],mp[maxn],dep[maxn],z,top[maxn],rmp[maxn],lef[maxn],rig[maxn];
struct sgt{
	struct node{
		LL sum,lz;
		node(){sum=0;lz=0;}
	}t[maxn<<2];
	#define ls i<<1
	#define rs i<<1|1
	#define lson i<<1,l,(l+r)/2
	#define rson i<<1|1,(l+r)/2+1,r
	void build(int i,int l,int r){
		if(l==r){t[i].sum=a[rmp[l]];return;}
		build(lson);build(rson);t[i].sum=t[ls].sum+t[rs].sum;
	}
	void pd(int i,int l,int r){
		if(t[i].lz){
			int mid=(l+r)/2;
			t[ls].sum+=(LL)(mid-l+1)*t[i].lz;
			t[ls].lz+=t[i].lz;
			t[rs].sum+=(LL)(r-mid)*t[i].lz;
			t[rs].lz+=t[i].lz;
			t[i].lz=0;
		}
	}
	void Add(int i,int l,int r,int l0,int r0,int d){
		if(l0<=l&&r0>=r){
			t[i].sum+=(LL)(r-l+1)*d;		
			t[i].lz+=d;
			return;
		}pd(i,l,r);
		if(l0<=(l+r)/2)Add(lson,l0,r0,d);
		if(r0>(l+r)/2)Add(rson,l0,r0,d);
		t[i].sum=t[ls].sum+t[rs].sum;
	}
	LL Qsum(int i,int l,int r,int l0,int r0){
		if(l0<=l&&r0>=r)return t[i].sum;
		pd(i,l,r);LL ans=0;
		if(l0<=(l+r)/2)ans+=Qsum(lson,l0,r0);
		if(r0>(l+r)/2)ans+=Qsum(rson,l0,r0);
		return ans;
	}
}T;
void dfs(int u){
	siz[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==fa[u])continue;
		dep[v]=dep[u]+1;fa[v]=u;
		dfs(v);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])son[u]=v;
	}
}
void build(int u,int tp){
	mp[u]=++z;top[u]=tp;rmp[z]=u;
	lef[u]=z;
	if(son[u])build(son[u],tp);
	for(int v,i=0;i<G[u].size();i++)if((v=G[u][i])!=fa[u]&&son[u]!=v)
		build(v,v);
	rig[u]=z;
}
LL Qsum(int u,int v){
	LL ans=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		ans+=T.Qsum(1,1,n,mp[top[u]],mp[u]);	
		u=fa[top[u]];
	}if(mp[u]>mp[v])swap(u,v);
	ans+=T.Qsum(1,1,n,mp[u],mp[v]);
	return ans;
}
int main(){
	n=getn();m=getn();
	for(int i=1;i<=n;i++)a[i]=getn();
	for(int i=1;i<n;i++){
		int u=getn(),v=getn();
		G[u].push_back(v);
		G[v].push_back(u);
	}dfs(1);build(1,1);
	T.build(1,1,n);
	while(m--){
		int op=getn();
		if(op==1){
			int x=getn(),a=getn();
			T.Add(1,1,n,mp[x],mp[x],a);
		}else if(op==2){
			int x=getn(),a=getn();
			T.Add(1,1,n,lef[x],rig[x],a);
		}else{
			printf("%lld\n",Qsum(1,getn()));
		}
	}
	return 0;
}
