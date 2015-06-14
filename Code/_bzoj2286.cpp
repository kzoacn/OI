#include<iostream>
#include<set>
#include<map>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
#include<bitset>
#include<stack>
#define inf 1e60
#define pa pair<int,int>
#define ll long long 
using namespace std;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int bin[20];
int n,m,cnt,ind,top;
int last[250005],last2[250005],fa[250005][20];
ll mn[250005],f[250005];
int h[250005],mark[250005],deep[250005];
int st[250005];
struct edge{
    int to,next,v;
}e[500005],ed[500005];
void insert(int u,int v,int w)
{
    e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;e[cnt].v=w;
    e[++cnt].to=u;e[cnt].next=last[v];last[v]=cnt;e[cnt].v=w;
}
void insert2(int u,int v)
{
    if(u==v)return;
    ed[++cnt].to=v;ed[cnt].next=last2[u];last2[u]=cnt;
}
bool cmp(int a,int b)
{
    return mark[a]<mark[b];
}
void pre(int x)
{
    mark[x]=++ind;
    for(int i=1;bin[i]<=deep[x];i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    for(int i=last[x];i;i=e[i].next)
        if(e[i].to!=fa[x][0])
        {
            mn[e[i].to]=min(mn[x],(ll)e[i].v);
            deep[e[i].to]=deep[x]+1;
            fa[e[i].to][0]=x;
            pre(e[i].to);
        }
}
int lca(int x,int y)
{
    if(deep[x]<deep[y])swap(x,y);
    int t=deep[x]-deep[y];
    for(int i=0;bin[i]<=t;i++)
        if(t&bin[i])x=fa[x][i];
    for(int i=19;i>=0;i--)
        if(fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    if(x==y)return x;
    return fa[x][0];
}
void dp(int x)
{
    f[x]=mn[x];
    ll tmp=0;
    for(int i=last2[x];i;i=ed[i].next)
    {
        dp(ed[i].to);
        tmp+=f[ed[i].to];
    }
    last2[x]=0;
    if(tmp==0)f[x]=mn[x];
    else if(tmp<=f[x])f[x]=tmp;
}
void solve()
{
    cnt=0;
    int K=read();
    for(int i=1;i<=K;i++)
        h[i]=read();
    sort(h+1,h+K+1,cmp);
    int tot=0;
    h[++tot]=h[1];
    for(int i=2;i<=K;i++)
        if(lca(h[tot],h[i])!=h[tot])h[++tot]=h[i];
    st[++top]=1;
    for(int i=1;i<=tot;i++)
    {
        int now=h[i],f=lca(now,st[top]);
        while(1)
        {
            if(deep[f]>=deep[st[top-1]])
            {
                insert2(f,st[top--]);
                if(st[top]!=f)st[++top]=f;
                break;
            }
            insert2(st[top-1],st[top]);top--;
        }
        if(st[top]!=now)st[++top]=now;
    }
    while(--top)insert2(st[top],st[top+1]);
    dp(1);
    printf("%lld\n",f[1]);
}
int main()
{
    bin[0]=1;for(int i=1;i<20;i++)bin[i]=bin[i-1]<<1;
    n=read();
    for(int i=1;i<n;i++)
    {
        int u=read(),v=read(),w=read();
        insert(u,v,w);
    }
    mn[1]=inf;pre(1);
    m=read();
    for(int i=1;i<=m;i++)
        solve();
    return 0;
}
