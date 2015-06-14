#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define P 55
#define N 5010
#define M 1001000
#define inf 0x3f3f3f3f
/*
2 <= N <= 50
1 <= M <= 2450
1 <= T <= 50
1 <= X,Y <= N
X != Y
1 <= Z <= 50
*/
using namespace std;
struct KSD
{
    int v,len,next;
}e[M];
int head[N],cnt;
int ru[2500],rv[2500],rl[2500];
inline void add(int u,int v,int len)
{
    e[++cnt].v=v;
    e[cnt].len=len;
    e[cnt].next=head[u];
    head[u]=cnt;
}
inline void Add(int u,int v,int len){add(u,v,len),add(v,u,0);}
int s,t,d[N];
queue<int>q;
bool bfs()
{
    while(!q.empty())q.pop();
    memset(d,0,sizeof d);

    int i,u,v;
    q.push(s),d[s]=1;
    while(!q.empty())
    {
        u=q.front(),q.pop();
        for(i=head[u];i;i=e[i].next)
        {
            if(!d[v=e[i].v]&&e[i].len)
            {
                d[v]=d[u]+1;
                if(v==t)return 1;
                q.push(v);
            }
        }
    }
    return 0;
}
int dinic(int x,int flow)
{
    if(x==t)return flow;
    int remain=flow,i,v,k;
    for(i=head[x];i&&remain;i=e[i].next)
    {
        if(d[v=e[i].v]==d[x]+1&&e[i].len)
        {
            k=dinic(v,min(remain,e[i].len));
            if(!k)d[v]=0;
            e[i].len-=k,e[i^1].len+=k;
            remain-=k;
        }
    }
    return flow-remain;
}
int n,m,p,maxflow;
int id[105][P],num;
void build(int p)
{
    int i,j,k;
    for(i=1;i<=n;i++)Add(id[p-1][i],id[p][i]=++num,inf);
    for(i=1;i<=m;i++)Add(id[p-1][ru[i]],id[p][rv[i]],rl[i]);
    Add(id[p][n],t,inf);
}
int main()
{
 //   freopen("test.in","r",stdin);

    int i,j,k;
    int a,b,c;
    scanf("%d%d%d",&n,&m,&p),cnt=1;
    if(n==1)
    {
        puts("0");
        return 0;
    }
    s=0,t=num=1,Add(s,2,p);
    for(i=1;i<=m;i++)scanf("%d%d%d",&ru[i],&rv[i],&rl[i]);
    for(i=1;i<=n;i++)id[1][i]=++num;
    for(i=2;i<=n+p;i++)
    {
        build(i);
        while(bfs())maxflow+=dinic(s,inf);
        if(maxflow==p)
        {
            printf("%d\n",i-1);
            return 0;
        }
    }
    puts("-1");
    return 0;
}
