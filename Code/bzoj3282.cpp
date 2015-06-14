#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+4;
int n,m;
struct node{
	int val,sum;
	bool rev;
	node *c[2],*f;
	void mkrev(){rev^=1;swap(c[0],c[1]);}
	void sets(node *x,int d){pd();if(x)x->f=this;c[d]=x;rz();}
	void rz(){sum=(c[0]?c[0]->sum:0)^val^(c[1]?c[1]->sum:0);}
	void pd(){if(rev){if(c[0])c[0]->mkrev();if(c[1])c[1]->mkrev();rev=0;}}
	int d(){return f->c[1]==this;}
	bool rt(){return !f||(f->c[0]!=this&&f->c[1]!=this);}
	node *C(int d){pd();return c[d];}
}nd[maxn],pool[maxn],*cur=pool;
void rot(node *x){
	node *y=x->f;if(!y->rt())y->f->pd();
	y->pd();x->pd();int d=x->d();y->sets(x->c[!d],d);
	if(y->rt())x->f=y->f;
	else y->f->sets(x,y->d());
	x->sets(y,!d);
}
void splay(node *x){
	while(!x->rt()){
		if(x->f->rt())rot(x);
		else if(x->f->d()==x->d())rot(x->f),rot(x);
		else rot(x),rot(x);
	}
}
node* access(node *x){
	static node* sta[maxn];
	static int top=0;
	node *y=x;
	while(y)sta[top++]=y,y=y->f;
	while(top)sta[--top]->pd();
	y=0;
	for(;x;x=x->f){
		splay(x);
		x->sets(y,1);
		y=x;
	}return y;
}
void mkrt(node *x){
	access(x)->mkrev();
}
node *findrt(node *u){
	access(u);
	splay(u);
	while(u->C(0))
	u=u->C(0);
	return u;
}
void link(node *u,node *v){
	if(findrt(u)!=findrt(v)){
		mkrt(u);
		u->f=v;
		access(u);
	}
}
node *findp(node *u){
	access(u);splay(u);
	u=u->C(0);while(u&&u->C(1))u=u->C(1);
	return u;
}
void cut(node *u,node *v){
	mkrt(u);
	if(findp(v)!=u)return;
	access(v);splay(v);
	v->c[0]=u->f=0;v->rz();
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&nd[i].val),nd[i].rz();
	while(m--){                    
		int op;scanf("%d",&op);
		int x,y;scanf("%d%d",&x,&y);
		if(op==0){
			node *u=nd+x,*v=nd+y;
			mkrt(u);
			access(v);
			splay(v);
			printf("%d\n",v->sum);
		}else
		if(op==1){
			node *u=nd+x,*v=nd+y;
			link(u,v);
		}else
		if(op==2){
			node *u=nd+x,*v=nd+y;
			cut(u,v);
		}else
		if(op==3){
			node *u=nd+x;
			mkrt(u);access(u);splay(u);
			u->val=y;u->rz();		
		}
	}
	return 0;
}
