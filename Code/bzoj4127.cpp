#include<iostream>
#include<cstring>
#include<cstdio>
#include<ctime>
#define maxn 100010
#define LL long long
#define l i<<1
#define r i<<1|1
#define mid (x+y)/2
#define lson x,mid
#define rson mid+1,y
#define inf 0x7fffffff
using namespace std;
int point[maxn],next[maxn*2],v[maxn*2],fa[maxn*2],h[maxn],top[maxn],size[maxn],son[maxn],p[maxn],pl[maxn],T=0;
LL w[maxn],ans;
struct hp{int sz1,sz2; LL w1,w2,wmax,wmin,lazy;}a[maxn*4];
void add(int x,int y,int i){
	v[i]=y; next[i]=point[x]; point[x]=i;}
void dfs1(int x,int dep){
	int i,k=-1;
	size[x]=1; h[x]=dep;
	for (i=point[x]; i; i=next[i])
	  if (v[i]!=fa[x]){
	  	fa[v[i]]=x;
	  	dfs1(v[i],dep+1);
	  	size[x]+=size[v[i]];
	  	if (size[v[i]]>k){
	  	  k=size[v[i]];
	  	  son[x]=v[i];
	  	}
	  }
}
void dfs2(int x){
	p[son[x]]=++T; pl[T]=son[x];
	top[son[x]]=top[x];
	if (son[son[x]]) dfs2(son[x]);
	for (int i=point[x]; i; i=next[i])
	  if (v[i]!=fa[x]&&v[i]!=son[x]){
	  	p[v[i]]=++T; pl[T]=v[i];
	  	top[v[i]]=v[i];
	  	if (son[v[i]]) dfs2(v[i]);
	  }
}
void updata(int i){
	a[i].sz1=a[l].sz1+a[r].sz1;
	a[i].sz2=a[l].sz2+a[r].sz2;
	a[i].w1=a[l].w1+a[r].w1;
	a[i].w2=a[l].w2+a[r].w2;
	a[i].wmax=max(a[l].wmax,a[r].wmax);
	a[i].wmin=min(a[l].wmin,a[r].wmin);
}
void build(int i,int x,int y){
	if (x==y){
	  LL d=w[pl[x]];
	  if (d>=0){
	  	a[i].sz1=1; a[i].w1=d;
	  	a[i].sz2=a[i].w2=a[i].wmax=0;
	  	a[i].wmin=inf;
	  }
	  else{
	  	a[i].sz2=1;
	  	a[i].sz1=a[i].w1=0;
	  	a[i].wmax=a[i].wmin=a[i].w2=-d;
	  }
	  a[i].lazy=0;
	  return;
	}
	build(l,lson); build(r,rson);
	updata(i);
}
bool paint(int i,int x,int y,LL num){
	if (!a[i].sz2){
	  a[i].w1+=a[i].sz1*num;
	  a[i].lazy+=num;
	  return true;
	}
	if (a[i].wmax<=num){
	  a[i].w1+=a[i].sz2*num-a[i].w2+a[i].sz1*num;
	  a[i].sz1+=a[i].sz2;
	  a[i].sz2=a[i].w2=a[i].wmax=0;
	  a[i].wmin=inf;
	  a[i].lazy+=num;
	  return true;
	}
	if (a[i].wmin>num){
	  a[i].w2-=a[i].sz2*num;
	  a[i].wmin-=num;
	  a[i].wmax-=num;
	  a[i].w1+=a[i].sz1*num;
	  a[i].lazy+=num;
	  return true;
	}
	return false;
}
void pushdown(int i,int x,int y){
	paint(l,lson,a[i].lazy);
	paint(r,rson,a[i].lazy);
	a[i].lazy=0;
}
void query(int i,int x,int y,int s,int t){
	if (x>=s&&y<=t){
	  ans+=a[i].w1+a[i].w2;
	  return;
	}
	if (a[i].lazy) pushdown(i,x,y);
	if (s<=mid) query(l,lson,s,t);
	if (t>mid) query(r,rson,s,t);
}
void insert(int i,int x,int y,int s,int t,LL num){
	if (x>=s&&y<=t){
	  if (paint(i,x,y,num)) return;
	}
	if (a[i].lazy) pushdown(i,x,y);
	if (s<=mid) insert(l,lson,s,t,num);
	if (t>mid) insert(r,rson,s,t,num);
	updata(i);
}
void tree_add(int vs,int vt,int x){
	while (top[vs]!=top[vt]){
		if (h[top[vs]]>h[top[vt]]){
		  insert(1,1,T,p[top[vs]],p[vs],x);
		  vs=fa[top[vs]];
		}
		else{
		  insert(1,1,T,p[top[vt]],p[vt],x);
		  vt=fa[top[vt]];
		}
	}
	if (h[vs]<h[vt]) insert(1,1,T,p[vs],p[vt],x);
	else insert(1,1,T,p[vt],p[vs],x);
}
void tree_query(int vs,int vt){
	ans=0;
	while (top[vs]!=top[vt]){
		if (h[top[vs]]>h[top[vt]]){
		  query(1,1,T,p[top[vs]],p[vs]);
		  vs=fa[top[vs]];
		}
		else{
		  query(1,1,T,p[top[vt]],p[vt]);
		  vt=fa[top[vt]];
		}
	}
	if (h[vs]<h[vt]) query(1,1,T,p[vs],p[vt]);
	else query(1,1,T,p[vt],p[vs]);
	printf("%lld\n",ans);
}
char buf[int(1e7)],*c=buf;
int in(){
	int re=0,f=1;
	while(!isdigit(*c))f=*c=='-'?-1:f,c++;
	while(isdigit(*c))re=re*10+*c-'0',c++;
	return re*f;
	
}
int main(){
freopen("bzoj4127.in","r",stdin);
	fread(buf,1,int(1e7),stdin);
	int n,m,i,x,y,k,vs,vt;
	n=in();m=in();
	for (i=1; i<=n; i++)
		w[i]=in();
	for (i=1; i<n; i++){
		x=in(),y=in();
	  add(x,y,l); add(y,x,r);
	}
	dfs1(1,1);
	p[1]=pl[1]=++T; top[1]=1;
	dfs2(1);
	build(1,1,n);
	for (i=1; i<=m; i++){
		k=in(),vs=in(),vt=in();
	  if (k==1){
	  x=in();
	  	tree_add(vs,vt,x);
	  }
	  else tree_query(vs,vt);
	}
	//cout<<clock();
}
