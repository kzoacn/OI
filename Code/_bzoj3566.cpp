#include<cstdio>
#include<cctype>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
  
typedef double f2;
  
#define N 500010
  
int head[N],next[N<<1],end[N<<1],pa[N];f2 p[N<<1],pp[N];
inline void addedge(int a,int b,f2 _p){static int q=1;end[q]=b,next[q]=head[a],head[a]=q,p[q++]=_p;}
inline void make(int a,int b,f2 _p){addedge(a,b,_p),addedge(b,a,_p);}
  
f2 f[N][2];
void dfs1(int x,int fa){
    for(int j=head[x];j;j=next[j]){
        if(end[j]!=fa){
            pp[end[j]]=p[j],pa[end[j]]=x,dfs1(end[j],x);
            f[x][0]*=f[end[j]][0]+(1-f[end[j]][0])*(1-pp[end[j]]);
        }
    }
}
void dfs2(int x,int fa){
    f2 t,_p;
    for(int j=head[x];j;j=next[j]){
        if(end[j]!=fa){
            t=f[end[j]][0]+(1-f[end[j]][0])*(1-pp[end[j]]);
            _p=t<1e-6?0:f[x][1]*f[x][0]/t;
            f[end[j]][1]=_p+(1-_p)*(1-pp[end[j]]);
            dfs2(end[j],x);
        }
    }
}
int main(){
	
    int n;cin>>n;
    register int i,j;int a,b,x;for(i=1;i<n;++i)scanf("%d%d%d",&a,&b,&x),make(a,b,x/100.0);
  
    for(i=1;i<=n;++i)scanf("%d",&x),f[i][0]=1-x/100.0;
    dfs1(1,-1),f[1][1]=1,dfs2(1,-1);
    f2 res=0;for(i=1;i<=n;++i)res+=1-f[i][0]*f[i][1];
    printf("%.6lf",res);
    return 0;
}
