#include<bits/stdc++.h>
#define mp(x) (lower_bound(w+1,w+1+w[0],x)-w)
#define c(x,d) (x?x->c[d]:0)
using namespace std;
const int maxn=8e4+5;
const int BIT=18;
int fa[maxn][BIT],dep[maxn];
int n,m,q,a[maxn],w[maxn<<1],lans;
vector<int>G[maxn];
struct node{
	int size;
	node *c[2];
	node *rz(){
		size=(c[0]?c[0]->size:0)+(c[1]?c[1]->size:0);
		return this;
	}
	node(){size=0;c[0]=c[1]=0;}
}*root[maxn];
queue<node*>qnode;
node *newnode(){
	return new node();
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
struct ufset{
	int fa[maxn],siz[maxn];
	void init(){for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1;}
	int find(int x){return fa[x]==x?x:find(fa[x]);}
	int size(int x){return siz[find(x)];}
	void merge(int x,int y){
		x=find(x);y=find(y);
		if(x==y)return;
		siz[x]+=siz[y];
		fa[y]=x;
	}
}S;
int vis[maxn],rt[maxn];
void dfs(int u){
	root[u]=insert(root[fa[u][0]],1,w[0],mp(a[u]));
	memset(fa[u]+1,0,sizeof (fa[u]+1));
	for(int i=1;i<BIT;i++)fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int v,i=0;i<G[u].size();i++){
		if((v=G[u][i])!=fa[u][0]){
			fa[v][0]=u;dep[v]=dep[u]+1;
			vis[v]=1;rt[v]=rt[u];dfs(v);
			S.merge(rt[u],v);			
		}
	}
}
void clear(node *x){
	if(!x)return;
	if(x->c[0])clear(x->c[0]);
	if(x->c[1])clear(x->c[1]);
	qnode.push(x);
}
void clear(int u){
	for(int v,i=0;i<G[u].size();i++){
		if((v=G[u][i])!=fa[u][0]){
			clear(v);			
		}
	}//clear(root[u]);
	root[u]=0;
}
void L(int x,int y){
	if(S.size(x)<S.size(y))swap(x,y);
	clear(rt[y]);
	fa[y][0]=x;rt[y]=rt[x];S.merge(x,y);dep[y]=dep[x]+1;
	G[x].push_back(y);
	G[y].push_back(x);
	dfs(y);
}
int main(){
	scanf("%*d%d%d%d",&n,&m,&q);S.init();
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),w[++w[0]]=a[i];
	for(int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}sort(w+1,w+1+w[0]);
	w[0]=unique(w+1,w+1+w[0])-w-1;
	for(int i=n;i>=1;i--){
		if(!vis[i]){
			rt[i]=i;
			vis[i]=1;
			dfs(i);
		}
	}
	while(q--){
		char op=getchar();while(!isalpha(op))op=getchar();
		if(op=='Q'){
			int x,y,k;scanf("%d%d%d",&x,&y,&k);
			x^=lans;y^=lans;k^=lans;
			printf("%d\n",lans=w[Q(root[x],root[y],root[fa[lca(x,y)][0]],root[lca(x,y)],1,w[0],k)]);
		}else{
			int x,y;scanf("%d%d",&x,&y);
			x^=lans;y^=lans;
			L(x,y);
		}
		
		
//		lans=0;
		
		
	}
	return 0;
}
