#include<bits/stdc++.h>
using namespace std;
int n,m,C,K;
int out[int(1e4+4)][10];
struct LCT{
	struct node{
		bool rev;
		int mx,val;
		node *f,*c[2];	
		bool d(){return this==f->c[1];}
		bool rt(){return !f||(f->c[0]!=this&&f->c[1]!=this);}
		void sets(node *x,int d){pd();if(x)x->f=this;c[d]=x;rz();}
		void makerv(){rev^=1;swap(c[0],c[1]);}
		void pd(){
			if(rev){
				if(c[0])c[0]->makerv();
				if(c[1])c[1]->makerv();
				rev=0;
			}
		}
		void rz(){
			mx=val;
			if(c[0])mx=max(mx,c[0]->mx);
			if(c[1])mx=max(mx,c[1]->mx);		
		}
	}nd[int(1e4)+1];
	void rot(node *x){
		node *y=x->f;if(!y->rt())y->f->pd();
		y->pd();x->pd();bool d=x->d();
		y->sets(x->c[!d],d);
		if(y->rt())x->f=y->f;
		else y->f->sets(x,y->d());
		x->sets(y,!d); 
	}
	void splay(node *x){
		while(!x->rt())
			if(x->f->rt())rot(x);
			else if(x->d()==x->f->d())rot(x->f),rot(x);
			else rot(x),rot(x);
	}
	node* access(node *x){
		node *y=0;
		for(;x;x=x->f){
			splay(x);
			x->sets(y,1);y=x;
		}return y;
	}
	void makert(node *x){
		access(x)->makerv();
		splay(x);
	}
	void link(node *x,node *y){
		makert(x);
		x->f=y;
		access(x);
	}
	void cut(node *x,node *y){
		makert(x);access(y);splay(y);
		y->c[0]=x->f=0;
		y->rz();
	}
	void link(int x,int y){link(nd+x,nd+y);}
	void cut(int x,int y){cut(nd+x,nd+y);}
	int Qmax(int u,int v){
		node *x=nd+u,*y=nd+v;
		if(!Con(u,v))return -1;
		makert(x);
		access(y);
		splay(y);
		return y->mx;
	}
	void C(int a,int b){
		node *x=nd+a;
		makert(x);
		splay(x);
		x->val=b;
		x->rz();
	}
	bool Con(int u,int v){
		node *x=nd+u,*y=nd+v;
		makert(x);
		access(y);
		splay(y);
		while(!x->rt())x=x->f;
		return x==y;
	}
	void deb(){
		for(int i=1;i<=n;i++){
			node *x=nd+i;
			printf("f:%d c[0]:%d c[1]:%d val:%d mx:%d rev:%d\n",x->f-nd,x->c[0]-nd,x->c[1]-nd,x->val,x->mx,x->rev);
		}puts("");
	}
}T[10];
int getn(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
struct edge{
	int u,v,c;
	bool operator<(edge o)const{
		return u!=o.u?u<o.u:v<o.v;
	}
}edges[int(1e5)];
int main(){
//	freopen("network1.in","r",stdin);
	n=getn();m=getn();C=getn();K=getn();
	for(int i=1;i<=n;i++){
		int val=getn();
		for(int j=0;j<C;j++)T[j].nd[i].val=val,T[j].nd[i].rz();
	}
	for(int i=0;i<m;i++){
		int u=getn(),v=getn(),c=getn();
		if(u>v)swap(u,v);
		edges[i]=(edge){u,v,c};
		T[c].link(u,v);
		out[u][c]++;
		out[v][c]++;
	}sort(edges,edges+m);
	while(K--){
		int op=getn();
		if(op==0){
			int x=getn(),y=getn();
			for(int i=0;i<C;i++)T[i].C(x,y);
		}else if(op==1){
			int u=getn(),v=getn(),c=getn();
			if(u>v)swap(u,v);
			if(!binary_search(edges,edges+m,(edge){u,v,c}))puts("No such edge.");
			else{
				int ps=lower_bound(edges,edges+m,(edge){u,v,c})-edges;
				int oc=edges[ps].c;
				if(c==oc){puts("Success.");continue;}
				if(out[u][c]+1>2||out[v][c]+1>2)puts("Error 1.");
				else if(T[c].Con(u,v))puts("Error 2.");
				else{
					out[u][oc]--;out[v][oc]--;
					out[u][c]++;out[v][c]++;
					edges[ps].c=c;
					T[oc].cut(u,v);
					T[c].link(u,v);
					puts("Success.");
				}
			}
		}else{
			int c=getn(),u=getn(),v=getn();
			printf("%d\n",T[c].Qmax(u,v));
		}
	}
	return 0;
}
