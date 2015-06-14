#include<bits/stdc++.h>
using namespace std;
const int maxn=40010;
struct node{
	int val,mx,mn,rev,sum,nag,pt;
	node *f,*c[2];
	void rz(){
		if(!pt)mx=mn=sum=val;
		else mx=-(~0u>>2),mn=~0u>>2,sum=0;
		if(c[0])mx=max(mx,c[0]->mx),mn=min(mn,c[0]->mn),sum+=c[0]->sum;
		if(c[1])mx=max(mx,c[1]->mx),mn=min(mn,c[1]->mn),sum+=c[1]->sum;
	}
	bool rt(){return !f||(f->c[0]!=this&&f->c[1]!=this);}
	void sets(node *x,int d){pd();if(x)x->f=this;c[d]=x;rz();}
	bool d(){return f->c[1]==this;}
	void makerv(){rev^=1;swap(c[0],c[1]);}
	void makeng(){nag^=1;swap(mx,mn);mx=-mx;mn=-mn;val=-val;sum=-sum;}
	void pd(){
		if(c[0]){if(rev)c[0]->makerv();if(nag)c[0]->makeng();}
		if(c[1]){if(rev)c[1]->makerv();if(nag)c[1]->makeng();}
		rev=nag=0;
	}
	//node(){val=sum=rev=0;c[0]=c[1]=0;}
}np[maxn],ne[maxn];
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
		x->sets(y,1);
		y=x;
	}return y;
}
void makert(node *x){
	access(x)->makerv();
	splay(x);
}
int getint(){
	int res=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
void link(node *u,node *v){
	makert(u);
	u->f=v;
	access(u);
}
int main(){
	int n=getint();
	for(int i=0;i<n;i++)np[i].pt=1;
	for(int i=1;i<n;i++){
		int u=getint(),v=getint(),w=getint();
		ne[i].val=w;ne[i].rz();
		link(np+u,ne+i);link(ne+i,np+v);
	}int m=getint();
	while(m--){
		char opt[10];scanf("%s",opt);
		if(opt[0]=='C'){
			node *u=ne+getint();int w=getint();
			makert(u);splay(u);u->pd();u->val=w;u->rz();
		}else if(opt[0]=='S'){
			node *u=np+getint(),*v=np+getint();
			makert(u);access(v);splay(v);
			printf("%d\n",v->sum);
		}else if(opt[0]=='N'){
			node *u=np+getint(),*v=np+getint();
			makert(u);access(v);splay(v);
			v->makeng();
		}else if(opt[1]=='A'){
			node *u=np+getint(),*v=np+getint();
			makert(u);access(v);splay(v);
			printf("%d\n",v->mx);
		}else if(opt[1]='I'){
			node *u=np+getint(),*v=np+getint();
			makert(u);access(v);splay(v);
			printf("%d\n",v->mn);	
		}
	}
	return 0;
}
