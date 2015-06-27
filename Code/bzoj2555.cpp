#include<bits/stdc++.h>
using namespace std;
const int maxn=1200005;
int son[maxn][26],len[maxn],fa[maxn];
int last=1,tot=1,root=1;
int newnode(int x){
    len[++tot]=x;
    return tot;
}
namespace LCT{
    struct node{
        bool rev;
        int val,laz;
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
            if(laz){
            	if(c[0])c[0]->laz+=laz,c[0]->val+=laz;
            	if(c[1])c[1]->laz+=laz,c[1]->val+=laz;
				laz=0;
			}
        }
        void rz(){
			  
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
        makert(nd+1);
    }
    void cut(node *x,node *y){
    	if(x==nd||y==nd)return;
        makert(x);access(y);splay(y);
        y->c[0]=x->f=0;
        y->rz();
    }
    void Add(node *x,node *y,int d){
		makert(x);access(y);
		splay(y);
		y->laz+=d;y->val+=d;y->pd();
	}
	int Qsum(node *x){
		makert(x);splay(x);return x->val;
	}
	node *fa(node *x){
		access(x);splay(x);
		x=x->c[0];
		if(!x)return nd;
		while(x->c[1])x=x->c[1];
		return x;
	}
	void makert(int x){makert(nd+x);}
    void link(int x,int y){link(nd+x,nd+y);}
    void cut(int x,int y){cut(nd+x,nd+y);}
    void Add(int x,int y,int d){Add(nd+x,nd+y,d);}
	int Qsum(int x){return Qsum(nd+x);}
	int fa(int x){return fa(nd+x)-nd;}
}
void add(int w){
    int p=last;
    int np=newnode(len[p]+1);
    LCT::makert(root);
    while(p&&!son[p][w])son[p][w]=np,p=LCT::fa(p);
    if(!p)LCT::link(np,root);//fa[np]=1;
    else{
        int q=son[p][w];
        if(len[p]+1==len[q])LCT::link(np,q);//fa[np]=q;
        else{
            int nq=newnode(len[p]+1);
            memcpy(son[nq],son[q],sizeof son[nq]);
            LCT::link(nq,LCT::fa(q));
			//fa[nq]=fa[q];
			
			LCT::cut(q,LCT::fa(q));
			LCT::makert(root);
			LCT::cut(np,LCT::fa(np));
			LCT::makert(root);
			
			LCT::link(q,nq);
			LCT::link(np,nq);
			//fa[q]=fa[np]=nq;
            while(p&&son[p][w]==q)son[p][w]=nq,p=LCT::fa(p);
        }
    }
	LCT::Add(1,np,1);
	last=np;
}
int mask,Q;
char s[maxn];
void decode(char *s,int n){
	for(int i=0;i<n;i++){
		mask=(mask*131+i)%n;
		swap(s[i],s[mask]);
	}
}
int main(){
	scanf("%d",&Q);
	scanf("%s",s);int n=strlen(s);
	for(int i=0;i<n;i++)
		add(s[i]-'a');
	while(Q--){
		char op[5];scanf("%s",op);
		if(op[0]=='A'){
			scanf("%s",s);n=strlen(s);
			decode(s,n);
			for(int i=0;i<n;i++)
				add(s[i]-'a');
		}else{
			scanf("%s",s);n=strlen(s);
			decode(s,n);
			int u=1;
			for(int i=0;i<n;i++)
				u=son[u][s[i]-'a'];
			printf("%d\n",LCT::Qsum(u));
		}
	}
    return 0;
}
