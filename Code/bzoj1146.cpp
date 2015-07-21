#include<bits/stdc++.h>
using namespace std;
const int maxn=80010;
int in(){
	int r=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:1,c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r*f;
}
int n,m;
int mp[maxn],fa[maxn],top[maxn],siz[maxn],son[maxn],dep[maxn],rmp[maxn],val[maxn];
vector<int>G[maxn];
void dfs(int u){
	siz[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==fa[u])continue;
		dep[v]=dep[u]+1;
		fa[v]=u;
		dfs(v);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])son[u]=v;
	}
}
int z;
void build(int u,int tp){
	mp[u]=++z;rmp[z]=u;top[u]=tp;
	if(son[u])build(son[u],tp);
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==son[u]||v==fa[u])continue;
		build(v,v);
	}
}
struct Treap{
	struct node{
		int key;
		int val;
		int siz,s;
		node *c[2];
		void rz(){siz=s;if(c[0])siz+=c[0]->siz;if(c[1])siz+=c[1]->siz;}
		node(int v=0){
			val=v;key=rand();
			siz=s=1;c[0]=c[1]=0;
		}
	}*root;
	Treap(){root=0;}
	void rot(node *&t,int d){
		node *p=t->c[d];t->c[d]=p->c[!d];
		p->c[!d]=t;t->rz();p->rz();t=p;
	}
	void insert(node *&t,int x){
		if(!t){t=new node(x);return;}
		if(t->val==x){t->s++;t->siz++;return;}
		insert(t->c[x>t->val],x);
		if(t->key>t->c[x>t->val]->key)
			rot(t,x>t->val);
		else t->rz();
	}
	void del(node *&t,int x){
//		if(!t)return;
		if(t->val==x){
			if(t->s>1){t->s--;t->siz--;return;}
			if(!t->c[0]){t=t->c[1];return;}
			if(!t->c[1]){t=t->c[0];return;}
			int d=t->c[0]->key>t->c[1]->key;
			rot(t,d);
			del(t,d);
			t->rz();
			return;
		}
		del(t->c[x>t->val],x);
		t->rz();
	}
	#define sz(x) (x?x->siz:0)
	int great(node *&t,int x){
		if(!t)return 0;
		if(t->val==x)return sz(t->c[1]);
		if(x<t->val)return t->s+sz(t->c[1])+great(t->c[0],x);
		if(x>t->val)return great(t->c[1],x);
	}
	void insert(int x){insert(root,x);}
	void del(int x){del(root,x);}
	int great(int x){return great(root,x);}
};
struct node{
	Treap T;
	int l,r;
}t[maxn*2];
int tot;
int buildT(int l,int r){
	int x=++tot;
	for(int i=l;i<=r;i++)
	t[x].T.insert(val[rmp[i]]);
	if(l==r)return x;
	int mid=(l+r)>>1;
	t[x].l=buildT(l,mid);
	t[x].r=buildT(mid+1,r);
	return x;
}
void C(int x,int l,int r,int ps,int od,int nw){
	t[x].T.del(od);
	t[x].T.insert(nw);	
	if(l==r)return;
	int mid=(l+r)>>1;
	if(ps<=mid)C(t[x].l,l,mid,ps,od,nw);
	else C(t[x].r,mid+1,r,ps,od,nw);
}
void C(int x,int y){
	C(1,1,n,mp[x],val[x],y);
	val[x]=y;
}
int great(int x,int l,int r,int l0,int r0,int y){
	if(l0>r0)swap(l0,r0);
	if(l0<=l&&r0>=r)return t[x].T.great(y);
	int ans=0,mid=(l+r)>>1;
	if(l0<=mid)ans+=great(t[x].l,l,mid,l0,r0,y);
	if(r0>mid)ans+=great(t[x].r,mid+1,r,l0,r0,y);
	return ans;
}
int mx=0;
int Qsum(int u,int v,int x){
	int ans=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		ans+=great(1,1,n,mp[u],mp[top[u]],x);
		u=fa[top[u]];
	}
	ans+=great(1,1,n,mp[v],mp[u],x);
	return ans;
}
int Q(int u,int v,int k){
	int l=0,r=mx;
	while(l<r){
		int mid=(l+r)>>1;
		int res=Qsum(u,v,mid);
		if(res>=k)
			l=mid+1;
		else r=mid;
	}return r;
}
int main(){	
//freopen("bzoj1146.in","r",stdin);
	n=in();m=in();
	for(int i=1;i<=n;i++)val[i]=in();
	mx=*max_element(val+1,val+1+n)+1;
	for(int i=1;i<n;i++){
		int u=in(),v=in();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1);
	build(1,1);
	
	buildT(1,n);
	
	while(m--){
		int k=in(),x=in(),y=in();
		if(!k){
			mx=max(mx,y+1);
			C(x,y);
		}else{
			if(Qsum(x,y,-1e9)<k)puts("invalid request!");
			else printf("%d\n",Q(x,y,k));
		}
	}
		
	return 0;
}
