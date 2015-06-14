/**************************************************************
    Problem: 2157
    User: Tunix
    Language: C++
    Result: Accepted
    Time:668 ms
    Memory:2600 kb
****************************************************************/
 
//BZOJ 2157
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define rep(i,n) for(int i=0;i<n;++i)
#define F(i,j,n) for(int i=j;i<=n;++i)
#define D(i,j,n) for(int i=j;i>=n;--i)
using namespace std;
int getint(){
    int v=0,sign=1; char ch=getchar();
    while(ch<'0'||ch>'9'){ if (ch=='-') sign=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){ v=v*10+ch-'0'; ch=getchar();}
    return v*=sign;
}
/******************tamplate*********************/
const int N=40010,INF=~0u>>2;
int n,m,cnt;
int ed[N];
int c[N][2],fa[N],v[N],sum[N],mn[N],mx[N];
bool rev[N],Not[N];
#define L c[x][0]
#define R c[x][1]
bool not_root(int x){
    return c[fa[x]][0]==x || c[fa[x]][1]==x;
}
void rever(int x){
    sum[x]=-sum[x]; v[x]=-v[x];
    swap(mn[x],mx[x]);
    mn[x]=-mn[x];mx[x]=-mx[x];
    Not[x]^=1;
}
void Push_up(int x){
    mx[x]=max(mx[L],mx[R]);
    mn[x]=min(mn[L],mn[R]);
    if (x>n){
        mx[x]=max(mx[x],v[x]);
        mn[x]=min(mn[x],v[x]);
    }
    sum[x]=sum[L]+sum[R]+v[x];
}
void Push_down(int x){
    if (Not[x]){
        Not[x]^=1;
        if (L) rever(L);
        if (R) rever(R);
    }
    if (rev[x]){
        rev[x]^=1; rev[L]^=1; rev[R]^=1;
        swap(L,R);
    }
}
void rotate(int x){
    int y=fa[x],z=fa[y],l=c[y][1]==x,r=l^1;
    if (not_root(y)) c[z][c[z][1]==y]=x;
    fa[x]=z; fa[y]=x; fa[c[x][r]]=y;
    c[y][l]=c[x][r]; c[x][r]=y;
    Push_up(y);
}
void preview(int x){
    if (not_root(x)) preview(fa[x]);
    Push_down(x);
}
void splay(int x){
    int y;
    for(preview(x);not_root(x);rotate(x))
        not_root(y=fa[x]) ? rotate(c[y][1]==x^c[fa[y]][1]==y ? x : y),1:1;
    Push_up(x);
}
void access(int x,int las=0){
    for(;x;splay(x),c[x][1]=las,las=x,x=fa[x]);
}
void makeroot(int x){
    access(x),splay(x),rev[x]^=1;
}
void link(int x,int y){
    makeroot(x),fa[x]=y;
}
void query(int x,int y){
    makeroot(x),access(y),splay(y);
}
int main(){
    n=getint();
    F(i,0,n) mn[i]=INF,mx[i]=-INF;
    int id=n;
    F(i,1,n-1){
        int x=getint()+1,y=getint()+1,w=getint();
        ed[i]=++id;
        link(x,id); link(y,id);
        v[id]=sum[id]=mx[id]=mn[id]=w;
    }
    m=getint();
    char cmd[5]; int x,y;
    F(i,1,m){
        scanf("%s",cmd);
        x=getint(); y=getint();
        if (cmd[0]=='C'){
            splay(ed[x]),v[ed[x]]=y,Push_up(ed[x]);
        }
        else if(cmd[0]=='N')
            query(x+1,y+1),rever(y+1);
        else if(cmd[0]=='S')
            query(x+1,y+1),printf("%d\n",sum[y+1]);
        else if(cmd[1]=='A')
            query(x+1,y+1),printf("%d\n",mx[y+1]);
        else query(x+1,y+1),printf("%d\n",mn[y+1]);
    }
    return 0;
}
