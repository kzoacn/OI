#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<string>
#define inf 1000000000
#define maxn 1000000+100
#define maxm 100000+100
#define eps 1e-10
#define ll long long
#define pa pair<int,int>
#define for0(i,n) for(int i=0;i<=(n);i++)
#define for1(i,n) for(int i=1;i<=(n);i++)
#define for2(i,x,y) for(int i=(x);i<=(y);i++)
#define for3(i,x,y) for(int i=(x);i>=(y);i--)
#define mod 20130426
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=10*x+ch-'0';ch=getchar();}
    return x*f;
}
int q,rt,t1,t2,tot,s[maxn],c[maxn][2],fa[maxn];
ll v[maxn],t[maxn][2],ans,base;
inline void pushup(int x)
{
 s[x]=s[c[x][0]]+s[c[x][1]]+1;
}
inline void rotate(int x,int &k)
{
 int y=fa[x],z=fa[y],l=c[y][1]==x,r=l^1;
 if(y!=k)c[z][c[z][1]==y]=x;else k=x;
 fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
 c[y][l]=c[x][r];c[x][r]=y;
 pushup(y);pushup(x);
}
inline void splay(int x,int &k)
{
 while(x!=k)
 {
  int y=fa[x],z=fa[y];
  if(y!=k)
  {
   if(c[z][0]==y^c[y][0]==x)rotate(x,k);else rotate(y,k);
  }
  rotate(x,k);
 }
}
inline void update(int x,ll xx,ll yy)
{
 if(!x)return;
 (v[x]=v[x]*yy+xx)%=mod;
 ((t[x][0]*=yy)+=xx)%=mod;
 (t[x][1]*=yy)%=mod;
}
inline void pushdown(int x)
{
 if(!x)return;
 if(!t[x][0]&&t[x][1]==1)return;
 update(c[x][0],t[x][0],t[x][1]);
 update(c[x][1],t[x][0],t[x][1]);
 t[x][0]=0;t[x][1]=1;
}
inline int find(int x,int k)
{
 pushdown(x);
 int l=c[x][0],r=c[x][1];
 if(s[l]+1==k)return x;
 else if(s[l]>=k)return find(l,k);
 else return find(r,k-s[l]-1);
}
inline void split(int l,int r)
{
 t1=find(rt,l);t2=find(rt,r);
 splay(t1,rt);splay(t2,c[t1][1]);
}
inline void calc(int x)
{
 if(!x)return;
 pushdown(x);
 calc(c[x][1]);
 if(x!=1)ans=(ans*base+v[x])%mod;
 calc(c[x][0]);
}
inline void build(int l,int r,int f)
{
 if(l>r)return;
 int x=(l+r)>>1;
 fa[x]=f;c[f][x>f]=x;
 s[x]=1;t[x][0]=0;t[x][1]=1;
 if(l==r)return;
 build(l,x-1,x);build(x+1,r,x);
 pushup(x);
} 
int main()
{
    freopen("bzoj3323.in","r",stdin);
    build(1,maxm,0);tot=maxm;rt=(1+maxm)>>1;
    q=read();char ch[maxn];
    while(q--)
    {
     scanf("%s",ch);
        if(ch[0]=='q')
        {
         ans=0;base=read()%mod;
         calc(rt);
            cout<<ans<<endl;
        }
        else 
        {
         int x=read()+1,y=read()+1;
         if(ch[3]=='x')
         {
          split(y,y+3);
          int z=c[t2][0],zz=c[z][0]+c[z][1];
          pushdown(t1);pushdown(t2);pushdown(z);
                v[z]+=v[zz];s[z]=1;
                fa[zz]=c[z][0]=c[z][1]=0;
                pushup(t2);pushup(t1);
                split(x,x+1);
                c[t2][0]=++tot;s[tot]=1;v[tot]=0;fa[tot]=t2;t[tot][1]=1;
                pushup(t2);pushup(t1);
         }
         else if(ch[0]=='m')
         {
          split(x,y+2);
          ll xx=0,yy=read()%mod;
          update(c[t2][0],xx,yy);
          pushup(t2);pushup(t1);
         }
         else 
         {
          split(x,y+2);
          ll xx=read()%mod,yy=1;
          update(c[t2][0],xx,yy);
          pushup(t2);pushup(t1);
         }
        }
 }
    return 0;
}
