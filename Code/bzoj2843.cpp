  
#include<bits/stdc++.h>
using namespace std;
const int maxn=30010;
int getint(){
    int res=0;char c=getchar();
    while(!isdigit(c))c=getchar();
    while(isdigit(c))res=res*10+c-'0',c=getchar();
    return res;
}
int n,m;
struct node{
    int val,sum,rev;
    node *c[2],*f;
    node(int _val=0){val=sum=_val;c[0]=c[1]=f=0;rev=0;}
    bool d(){return f->c[1]==this;}
    void sets(node *x,int d){pd();if(x)x->f=this;c[d]=x;rz();}
    void rz(){sum=(c[0]?c[0]->sum:0)+val+(c[1]?c[1]->sum:0);}
    bool rt(){return !f||(f->c[0]!=this&&f->c[1]!=this);}
    void mkrev(){rev^=1;swap(c[0],c[1]);}
    void pd(){if(rev){if(c[0])c[0]->mkrev();if(c[1])c[1]->mkrev();rev=0;}}
}nd[maxn];
void rot(node *x){
    node *y=x->f;if(!y->rt())y->f->pd();
    y->pd();x->pd();int d=x->d();y->sets(x->c[!d],d);
    if(y->rt())x->f=y->f;
    else y->f->sets(x,y->d());
    x->sets(y,!d);
}
void splay(node *x){
    for(;!x->rt();rot(x))if(x->f->rt());
    else if(x->d()==x->f->d())rot(x->f);
    else rot(x);
}
node *access(node *x){
    node *y=0;
    for(;x;x=x->f){
        splay(x);
        x->sets(y,1);
        y=x;
    }return y;
}
void mkrt(node *x){
    access(x)->mkrev();
    splay(x);
}
node *findrt(node *x){
    access(x);
    splay(x);
    node *u=x;
    while(u->c[0])
    u=u->c[0];
    return u;
}
void link(node *x,node *y){
    if(findrt(x)==findrt(y))return void(puts("no"));
    mkrt(x);
    x->f=y;
    puts("yes");
}
void putint(int x){
    if(x<10)putchar(x+'0');
    else {putint(x/10);putchar(x%10+'0');}
}
int main(){
    n=getint();
    for(int i=1;i<=n;i++)nd[i].val=getint(),nd[i].rz();
    m=getint();
    while(m--){
        char op[10];scanf("%s",op);
        if(op[0]=='b'){
            int x=getint(),y=getint();
            link(nd+x,nd+y);
        }else
        if(op[0]=='p'){
            int x=getint(),y=getint();
            mkrt(nd+x);
            nd[x].val=y;nd[x].rz();
        }else{
            node *x=nd+getint();
            node *y=nd+getint();
            if(findrt(x)!=findrt(y))puts("impossible");
            else{
                mkrt(x);
                access(y);
                splay(y);
                putint(y->sum);puts("");
            }
        }
    }
    return 0;
}
