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

#define maxn 200000+5

#define maxm 200000+5

#define eps 1e-10

#define ll long long

#define pa pair<int,int>

#define for0(i,n) for(int i=0;i<=(n);i++)

#define for1(i,n) for(int i=1;i<=(n);i++)

#define for2(i,x,y) for(int i=(x);i<=(y);i++)

#define for3(i,x,y) for(int i=(x);i>=(y);i--)

#define for4(i,x) for(int i=head[x],y;i;i=e[i].next)

#define mod 1000000007

using namespace std;

inline int read()

{

    int x=0,f=1;char ch=getchar();

    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}

    while(ch>='0'&&ch<='9'){x=10*x+ch-'0';ch=getchar();}

    return x*f;

}
int  n,m,s,t,tot=1,head[maxn],cur[maxn],h[maxn],num[100][100];
double maxflow,a[100][100][3];
queue<int>q;
struct edge{int go,next;double v;}e[maxm];
inline void add(int x,int y,double v)
{
    e[++tot]=(edge){y,head[x],v};head[x]=tot;
    e[++tot]=(edge){x,head[y],0};head[y]=tot;
}
bool bfs()
{
    for(int i=s;i<=t;i++)h[i]=-1;
    q.push(s);h[s]=0;
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=e[i].next)
         if(e[i].v>eps&&h[e[i].go]==-1)
         {
            h[e[i].go]=h[x]+1;q.push(e[i].go);
         }
    }
    return h[t]!=-1;
}
double dfs(int x,double f)
{
    if(x==t) return f;
    double tmp,used=0.0;
    for(int i=cur[x];i;i=e[i].next)
     if(e[i].v>eps&&h[e[i].go]==h[x]+1)
    {
        tmp=dfs(e[i].go,min(e[i].v,f-used));
        e[i].v-=tmp;if(e[i].v>eps)cur[x]=i;
        e[i^1].v+=tmp;used+=tmp;
        if(fabs(used-f)<eps)return f;       
    }
    if(used<eps) h[x]=-1;
    return used;
}
void dinic()
{
    maxflow=0.0;
    while(bfs())
    {
        for (int i=s;i<=t;i++)cur[i]=head[i];maxflow+=dfs(s,inf);
    }
}
bool check(double mid)
{
    double ret=0.0;
    memset(head,0,sizeof(head));tot=1;
    for0(i,n+1)for0(j,m+1)
    if(i&&i<n+1&&j&&j<m+1)add(s,num[i][j],a[i][j][0]),ret+=a[i][j][0];
    else add(num[i][j],t,inf);
    for0(i,n)for1(j,m)add(num[i][j],num[i+1][j],mid*a[i][j][1]),add(num[i+1][j],num[i][j],mid*a[i][j][1]);
    for1(i,n)for0(j,m)add(num[i][j],num[i][j+1],mid*a[i][j][2]),add(num[i][j+1],num[i][j],mid*a[i][j][2]);
    dinic();
    return ret-maxflow>1e-9;
}

int main()

{

    n=read();m=read();
    for0(i,n+1)for0(j,m+1)num[i][j]=++tot;s=0;t=++tot;
    for1(i,n)for1(j,m)a[i][j][0]=read();
    for0(i,n)for1(j,m)a[i][j][1]=read();
    for1(i,n)for0(j,m)a[i][j][2]=read();
    double l=0,r=n*m*100;
    while(r-l>1e-5)
    {
        double mid=(l+r)/2;
        if(check(mid))l=mid;else r=mid;
    }
    printf("%.3f\n",l);

    return 0;

}
