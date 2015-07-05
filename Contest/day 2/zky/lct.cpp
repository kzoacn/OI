#include<cstdio>
#include<cctype>
#include<iostream>
#include<algorithm>
#include<vector>
#include<deque>
using namespace std;
const int maxn=2e5+5;
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
int n,m;
int val[maxn],fa[maxn],dep[maxn],mp[maxn],z,rmp[maxn];
vector<int>G[maxn];
void dfs(int u){
	mp[u]=++z;rmp[z]=u;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==fa[u])continue;
		dep[v]=dep[u]+1;fa[v]=u;
		dfs(v);
	}
}
namespace BF{
	void dfs(int u){
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(v==fa[u])continue;
			dep[v]=dep[u]+1;fa[v]=u;
			dfs(v);
		}
	}
	int la;
	int Q(int u,int v){
		deque<int>d1,d2;
		while(dep[u]>dep[v])d1.push_back(u),u=fa[u];
		while(dep[u]<dep[v])d2.push_front(v),v=fa[v];
		while(u!=v){
			d1.push_back(u),u=fa[u];
			d2.push_front(v),v=fa[v];
		}
		vector<int>vec;
		for(int i=0;i<d1.size();i++)vec.push_back(d1[i]);
		vec.push_back(v);
		for(int i=0;i<d2.size();i++)vec.push_back(d2[i]);
		int mn=val[vec[0]];
		int ans=0;
		for(int i=1;i<vec.size();i++)
			mn=min(mn,val[vec[i]]),ans=max(ans,val[vec[i]]-mn);
		return ans;
	}
	int solve(){
		dfs(1);
		while(m--){
			int ty=in();
			if(ty==1){
				int u=in()^la,v=in()^la;
				printf("%d\n",la=Q(u,v));	
			}else{
				int v=in(),f=in()^la;
				n++;val[n]=v;
				G[f].push_back(n);
				dfs(1);
			}
		}
		return 0;
	}
}
struct info{
	int pans,sans;
	int mn,mx;
	info(int val=0){
		pans=sans=0;
		mn=mx=val;
	}
};	
info operator+(const info &A,const info &B){
	info I;
	I.pans=max(A.pans,B.pans);
	I.pans=max(I.pans,B.mx-A.mn);
	I.sans=max(A.sans,B.sans);
	I.sans=max(I.sans,A.mx-B.mn);
	I.mx=max(A.mx,B.mx);
	I.mn=min(A.mn,B.mn);
	return I;
}
struct node{
    bool rev;
    int val;
    info I;
    node *f,*c[2];  
    bool d(){return this==f->c[1];}
    bool rt(){return !f||(f->c[0]!=this&&f->c[1]!=this);}
    void sets(node *x,int d){pd();if(x)x->f=this;c[d]=x;rz();}
    void makerv(){
    	rev^=1;
    	swap(c[0],c[1]);
    	swap(I.pans,I.sans);
    }
	void pd(){
	    if(rev){
            if(c[0])c[0]->makerv();
            if(c[1])c[1]->makerv();
            rev=0;
        }
    }
    void rz(){
        I=info(val);
        if(c[0])I=c[0]->I+I;
        if(c[1])I=I+c[1]->I;
    }
}nd[maxn];
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
void link(int x,int y){link(nd+x,nd+y);}
int Q(int u,int v){
	node *x=nd+u,*y=nd+v;
	makert(x);access(y);splay(y);
	return y->I.pans;
}
int main(){
	freopen("lct.in","r",stdin);
	freopen("lct.out","w",stdout);
	n=in();
	for(int i=1;i<=n;i++)nd[i].val=val[i]=in(),nd[i].rz();
	for(int i=1;i<n;i++){
		int u=in(),v=in();
		G[u].push_back(v);
		G[v].push_back(u);
		link(u,v);
	}
	m=in();
	if(n<=2000&&m<=2000)return BF::solve();	
	int la=0;
	while(m--){
		int ty=in();
		if(ty==1){
			int u=in()^la,v=in()^la;
			printf("%d\n",la=Q(u,v));	
		}else{
			int v=in(),f=in()^la;
			n++;nd[n].val=v;nd[n].rz();
			link(f,n);
		}
	}
	return 0;
}
