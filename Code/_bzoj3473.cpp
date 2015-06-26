#include<cstdio>
#include<cstring>
#include<cctype>
#include<iostream>
#include<algorithm>
using namespace std;
  
#define N 100010
  
int tranc[N<<1][26],len[N<<1],pa[N<<1],cnt,root,last;
inline int newnode(int l){len[++cnt]=l;return cnt;}
  
struct Graph{
    int head[N<<1],next[N<<1],end[N<<1],ind;
    inline void addedge(int a,int b){int q=++ind;end[q]=b,next[q]=head[a],head[a]=q;}
}w,g,sav;
  
char s[N];
  
int seq[N<<1],in[N<<1],out[N<<1],tclock;
inline void dfs(int x){
    in[x]=++tclock,seq[tclock]=x;
    for(int j=g.head[x];j;j=g.next[j])dfs(g.end[j]);
    out[x]=tclock;
}
  
struct Ask{
    int lab,l,r;
    Ask(){}
    Ask(int _lab,int _l,int _r):lab(_lab),l(_l),r(_r){}
    bool operator<(const Ask&B)const{return r<B.r;}
}S[N<<1];
  
int ans[N<<1],lastins[N];
  
int A[N<<1];
inline void mdf(int x,int add){
    for(;x<=cnt;x+=x&-x)A[x]+=add;
}
inline int ask(int x){
    int r=0;for(;x;x-=x&-x)r+=A[x];return r;
}
  
int v[N<<1];
  
void dfs2(int x){
    v[x]+=v[pa[x]];
    for(int j=g.head[x];j;j=g.next[j])dfs2(g.end[j]);
}
  
void get(int x){
    for(int j=w.head[x];j;j=w.next[j])printf("%d ",w.end[j]);puts("");
}
  
int main(){
    int n,lim;scanf("%d%d",&n,&lim);
      
    register int i,j,k;int y;int p,np,q,nq,rep,tmp;
    for(root=newnode(0),i=1;i<=n;++i){
        scanf("%s",s);int l=strlen(s);
        for(last=root,j=l-1;j>=0;--j){
            if((p=tranc[last][y=s[j]-'a'])!=0){
                if(len[p]==len[last]+1)last=p;
                else{
                    rep=newnode(len[last]+1);pa[rep]=pa[p],pa[p]=rep;
                    memcpy(tranc[rep],tranc[p],sizeof tranc[p]);
                    for(tmp=last;tmp&&tranc[tmp][y]==p;tmp=pa[tmp])tranc[tmp][y]=rep;
                    last=rep;
                }
            }
            else{
                np=newnode(len[last]+1);
                for(p=last;p&&!tranc[p][y];p=pa[p])tranc[p][y]=np;
                if(!p)pa[np]=root;
                else{
                    q=tranc[p][y];
                    if(len[q]==len[p]+1)pa[np]=q;
                    else{
                        nq=newnode(len[p]+1),pa[nq]=pa[q],pa[np]=pa[q]=nq;
                        memcpy(tranc[nq],tranc[q],sizeof tranc[q]);
                        for(;p&&tranc[p][y]==q;p=pa[p])tranc[p][y]=nq;
                    }
                }last=np;
            }
            w.addedge(last,i);
            sav.addedge(i,last);
        }
    }
      
    for(i=1;i<=cnt;++i)if(pa[i])g.addedge(pa[i],i);
    dfs(1);
      
    for(i=1;i<=cnt;++i)S[i]=Ask(i,in[i],out[i]);sort(S+1,S+cnt+1);
    for(k=i=1;i<=cnt;++i){
        for(j=w.head[seq[i]];j;j=w.next[j]){
            if(lastins[w.end[j]])mdf(lastins[w.end[j]],-1);mdf(lastins[w.end[j]]=i,1);
        }
        for(;S[k].r==i;++k)ans[S[k].lab]=ask(S[k].r)-ask(S[k].l-1);
    }
      
    for(i=1;i<=cnt;++i)v[i]=ans[i]>=lim?len[i]-len[pa[i]]:0;
      
    dfs2(1);
      
    long long nowans;
    for(i=1;i<=n;++i){
        if(i>1)putchar(' ');
        for(nowans=0,j=sav.head[i];j;j=sav.next[j])nowans+=v[sav.end[j]];
        printf("%lld",nowans);
    }puts("");
    return 0;
}
