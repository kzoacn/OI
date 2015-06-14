#include<bits/stdc++.h>
#define V(x) (LCT::pool+x)
#define E(x) (LCT::pool+n+x)
using namespace std;
const int maxn=100010;
const int maxm=1000010;
int n,m,q,anss[maxn];
struct edge{int u,v,w,f,id;bool operator<(const edge o)const{return w<o.w;}}edges[maxm],_edges[maxm];
struct qes{int op,x,y;}Q[maxn];
namespace LCT{
	struct node{
		int rev,val,sum;
		node *c[2],*p,*mx;
		void makerev(){rev^=1;swap(c[0],c[1]);}
		void pd(){if(rev){rev=0;c[0]->makerev();c[1]->makerev();}}
		void rz(){
			sum=c[0]->sum^val^c[1]->sum;
		}
		void sets(node *x,int d){pd();(c[d]=x)->p=this;rz();}
		bool d(){return p->c[1]==this;}
		bool rt(){return p->c[0]!=this&&p->c[1]!=this;}
	}*null,pool[maxn+maxm];
	node *newnode(int _val=0){
		static node *x=pool;x->rev=0;x->val=_val;
		x->c[0]=x->c[1]=x->p=null;x->mx=x;
		return x++;
	}
	void init(){
		null=newnode();
		null->c[0]=null->c[1]=null->p=null->mx=null;
		int x;
		for(int i=1;i<=n;i++)scanf("%d",&x),newnode(x);
	}
	void rot(node *x){
		node *y=x->p;if(!y->rt())y->p->pd();
		y->pd();x->pd();int d=x->d();
		y->sets(x->c[!d],d);
		if(y->rt())x->p=y->p;
		else y->p->sets(x,y->d());
		x->sets(y,!d);
	}
	void splay(node *x){
		for(;!x->rt();rot(x))if(x->p->rt());
		else if(x->d()==x->p->d())rot(x->p);
		else rot(x);
	}
	node *access(node *x){
		node *y=null;
		for(;x!=null;x=x->p)splay(x),x->sets(y,1),y=x;
		return y;
	}
	void makert(node *x){
		access(x)->makerev();splay(x);
	}
	node *findp(node *x){
		access(x);splay(x);
		x->pd();x->c[1];
		
	}
	node *findrt(node *x){
		
	}
	void link(node *x,node *y){
		if(findrt(x)==findrt(y))return;
		makert(x);
		x->p=y;
		access(x);
	}
	void cut(node *x,node *y){
		makert(x);
		if(findp(y)!=x)return;
		access(y);splay(y);
		y->c[0]=x->p=null;y->rz();
	}
	node *Qmax(node *x,node *y){
		makert(x);access(y);splay(y);
		return y->mx;
	}
}
int getint(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}typedef pair<int,int> pi;map<pi,int>M;
int fa[maxn];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
int main(){
	scanf("%d%d",&n,&m);LCT::init();
	while(m--){
		int op,x,y;scanf("%d%d%d",&op,&x,&y);
		if(op==0){
			node *u=
		}else
		if(op==1){
		
		}else
		if(op==2){
		
		}else
		if(op==3){
		
		}
	}	
	return 0;
}
