#include<bits/stdc++.h>
using namespace std;
const int maxn=30010;
struct node{
	int val,sum,rev;
	node *c[2],*f;
	void rv(){rev^=1;swap(c[0],c[1]);}
	bool d(){return f->c[1]==this;}
	bool rt(){return !f||(f->c[0]!=this&&this!=f->c[1]);}
	void sets(node *x,int d){pd();if(x)x->f=this;c[d]=x;rz();}
	void pd(){
		if(rev){
			if(c[0])c[0]->rv();
			if(c[1])c[1]->rv();
			rev=0;
		}
	}
	void rz(){
		sum=val;
		if(c[0])sum+=c[0]->sum;
		if(c[1])sum+=c[1]->sum;
	}
}nd[maxn];
void rot(node *x){
	node *y=x->f;if(!y->rt())y->f->pd();
	y->pd();x->pd();int d=x->d();
	y->sets(x->c[!d],d);
	if(y->rt())x->f=y->f;
	else y->f->sets(x,y->d());
	x->sets(y,!d);
}
void splay(node *x){
	while(!x->rt()){
		if(x->f->rt())rot(x);
		else if(x->d()==x->f->d())rot(x->f),rot(x);
		else rot(x),rot(x);
	}
}
node* access(node *x){
	node *y=0;
	for(;x;x=x->f){
		splay(x);
		x->sets(y,1);y=x;
	}return y;
}
void makrt(node *x){
	access(x)->rv();
	splay(x);
}
bool conn(node *x,node *y){
	makrt(x);
	access(y);
	splay(y);
	while(!x->rt())x=x->f;
	return x==y;
}
void link(node *x,node *y){
	if(conn(x,y))return void(puts("no"));
	puts("yes");
	makrt(x);
	x->f=y;
	access(x);
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&nd[i].val),nd[i].rz();
	int m;scanf("%d",&m);
	while(m--){
		char op[33];
		scanf("%s",op);
		if(op[0]=='b'){
			int u,v;scanf("%d%d",&u,&v);
			link(nd+u,nd+v);
		}else if(op[0]=='e'){
			int u,v;scanf("%d%d",&u,&v);
			node *x=nd+u,*y=nd+v;
			if(!conn(x,y)){
				puts("impossible");
				continue;
			}
			makrt(x);
			access(y);
			splay(y);
			printf("%d\n",y->sum);			
		}else{
			int u,a;scanf("%d%d",&u,&a);
			node *x=nd+u;
			makrt(x);
			splay(x);
			x->val=a;x->rz();
		}
	}
	return 0;
}
