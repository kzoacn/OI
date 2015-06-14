#include<bits/stdc++.h>
#define mp(x) (lower_bound(w+1,w+1+w[0],x)-w)
#define c(x,d) (x?x->c[d]:0)
using namespace std;
const int maxn=1e5+5;
const int BIT=18;
int fa[maxn][BIT],dep[maxn];
int n,m,a[maxn],w[maxn<<1];
vector<int>G[maxn];
struct node{
	int size;
	node *c[2];
	node *rz(){
		size=(c[0]?c[0]->size:0)+(c[1]?c[1]->size:0);
		return this;
	}
}*root[maxn],pool[maxn*BIT+10],*cur=pool;
queue<node*>qnode;
node *newnode(){
	return cur++;
}
node *insert(node *x,int l,int r,int val){
	node *y=newnode();
	if(x)*y=*x,y->size++;
	else y->size=1;
	if(l==r)return y;
	int mid=(l+r)>>1;
	if(val<=mid)
		y->c[0]=insert(c(x,0),l,mid,val);	
	else y->c[1]=insert(c(x,1),mid+1,r,val);
	return y->rz();
}
int size(node *x,node *y,node *z,node *w){
	return (x&&x->c[0]?x->c[0]->size:0)+(y&&y->c[0]?y->c[0]->size:0)-(z&&z->c[0]?z->c[0]->size:0)-(w&&w->c[0]?w->c[0]->size:0);
}
int Q(node *x,node *y,node *z,node *w,int l,int r,int k){
	if(l==r)return l;
	int mid=(l+r)>>1;
	int siz=size(x,y,z,w);
	if(siz>=k)return Q(c(x,0),c(y,0),c(z,0),c(w,0),l,mid,k);
	else return Q(c(x,1),c(y,1),c(z,1),c(w,1),mid+1,r,k-siz);
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=BIT-1;i>=0;i--)if(dep[u]-(1<<i)>=dep[v])u=fa[u][i];
	if(u!=v){
		for(int i=BIT-1;i>=0;i--)if(fa[u][i]!=fa[v][i])
		u=fa[u][i],v=fa[v][i];
		u=fa[u][0];v=fa[v][0];
	}return u;
}
void dfs(int u){
	root[u]=insert(root[fa[u][0]],1,w[0],mp(a[u]));
	for(int i=1;i<BIT;i++)fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int v,i=0;i<G[u].size();i++){
		if((v=G[u][i])!=fa[u][0]){
			fa[v][0]=u;dep[v]=dep[u]+1;
			dfs(v);			
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),w[++w[0]]=a[i];
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}static int _u[maxn],_v[maxn],_k[maxn];
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&_u[i],&_v[i],&_k[i]);
//		w[++w[0]]=_k[i];
	}sort(w+1,w+1+w[0]);
	w[0]=unique(w+1,w+1+w[0])-w-1;
	dfs(1);int lans=0;
	for(int i=1;i<=m;i++){
		int u=_u[i]^lans,v=_v[i],k=_k[i];
		printf("%d",lans=w[Q(root[u],root[v],root[fa[lca(u,v)][0]],root[lca(u,v)],1,w[0],k)]);
		if(i!=m)puts("");
//		lans=0;
		
	}
	return 0;
}
