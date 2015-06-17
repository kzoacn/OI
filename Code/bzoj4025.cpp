#include<ctime>
#include<cctype>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=1e5+5;
const int maxm=2e5+5;
int n,m,T,cot;
int tag[maxm],tree[maxm];
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
struct edge{int u,v;}E[maxm];
struct node{
	int val,siz,rev;
	node *mn;
	node *c[2],*f;
	bool d(){return f->c[1]==this;}
	bool rt(){return !f||(f->c[0]!=this&&f->c[1]!=this);}
	void sets(node *x,int d){pd();c[d]=x;if(x)x->f=this;rz();}
	void rv(){rev^=1;swap(c[0],c[1]);}
	void pd(){
		if(rev){
			if(c[0])c[0]->rv();
			if(c[1])c[1]->rv();
			rev^=1;
		}		
	}
	void rz();
}nd[maxn],ne[maxm];
void deb();
void node::rz(){
	mn=this;siz=((1<=this-ne)&&(this-ne<=m));
	if(c[0])siz+=c[0]->siz;
	if(c[1])siz+=c[1]->siz;
	if(c[0]&&c[0]->mn->val<mn->val)mn=c[0]->mn;
	if(c[1]&&c[1]->mn->val<mn->val)mn=c[1]->mn;
}
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
	access(x)->rv();
	splay(x);
}
bool conn(node *u,node *v){
	makert(u);
//	deb();
	access(v);
//	deb();
	splay(v);
//	deb();
	while(!u->rt())u=u->f;
	return u==v;
}
void link(node *u,node *v){
	makert(u);
//	splay(u);
	u->f=v;
	access(u);
}
void cut(node *u,node *v){
	makert(u);
	access(v);
	splay(v);
	v->c[0]=u->f=0;v->rz();
}
node *Qmin(node *u,node *v){
	makert(u);
	access(v);
	splay(v);
	return v->mn;
}
int Qsiz(node *u,node *v){
	makert(u);
	access(v);
	splay(v);
	return v->siz;
}
void add(int id){
	node *u=nd+E[id].u;
	node *v=nd+E[id].v;
	node *e=ne+id;
//	deb();
	if(!conn(u,v)){
		link(u,e);
		link(e,v);
		tree[id]=1;
		return;
	}
//	deb();
	node *mn=Qmin(u,v);
	if(e->val>mn->val){
		int idx=mn-ne;
		cut(nd+E[idx].u,ne+idx);
		cut(nd+E[idx].v,ne+idx);
		link(u,e);
		link(e,v);
		tree[idx]=0;tree[id]=1;
		u=nd+E[idx].u;v=nd+E[idx].v;
		swap(e,mn);
		swap(id,idx);
	}else tree[id]=0;
	int siz=Qsiz(u,v);
	if(siz%2==0)
		tag[id]=1,cot++;	
}
void del(int id){
	if(tree[id]){
		cut(nd+E[id].u,ne+id);
		cut(ne+id,nd+E[id].v);
		tree[id]=0;
		return ;
	}
	if(tag[id]){
		cot--;
		tag[id]=0;
	}
}
struct task{
	int id,ti,ty;
	bool operator<(task o)const{return ti!=o.ti?ti<o.ti:ty<o.ty;}
}t[maxm*2];
int ts;
int ind(node* x){
	if(!x)return 0;
	if((1<=int(x-nd))&&(int(x-nd)<=n))
		return x-nd;
	else return x-ne;
}
void deb(node *x){
	if(1<=int(x-nd)&&int(x-nd)<=n){
		printf("f:e%d c[0]:e%d c[1]:e%d rev:%d\n",ind(x->f),ind(x->c[0]),ind(x->c[1]),x->rev);
	}else{
		printf("f:v%d c[0]:v%d c[1]:v%d rev:%d\n",ind(x->f),ind(x->c[0]),ind(x->c[1]),x->rev);
	}
}
void deb(){
	for(int i=1;i<=n;i++)deb(nd+i);
	for(int i=1;i<=m;i++)deb(ne+i);
	puts("");
}
int main(){
	freopen("bzoj4025.in","r",stdin);
	n=in();m=in();T=in();
	for(int i=1;i<=m;i++){
		int u=in(),v=in(),st=in(),ed=in();
		E[i].u=u;E[i].v=v;ne[i].val=ed;ne[i].rz();
		if(ed==st)continue;
		t[ts++]=(task){i,st,1};
		t[ts++]=(task){i,ed,-1};
	}sort(t,t+ts);
	for(int i=1;i<=n;i++)nd[i].val=1e9;
	int now=0;
	for(int i=0;i<ts;){
		while(i<ts&&now==t[i].ti){
			if(t[i].ty==-1)del(t[i].id);
			else add(t[i].id);
			i++;
//			deb();
		}
		while(now<T&&(i<ts&&now<t[i].ti))
			now++,puts(cot?"No":"Yes");
	}
	while(now<T)
		now++,puts(cot?"No":"Yes");
	return 0;
}
