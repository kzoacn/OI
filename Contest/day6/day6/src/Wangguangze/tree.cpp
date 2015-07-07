#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<vector>
#include<set>
#include<map>
#define LL long long 
#define inf 0x7fffffff

using namespace std;
int read()
{
    int x=0,f=1; char ch=getchar();
    while (ch<'0' || ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    return x*f;
}

struct data{ 
    int d1[2],d2[2],d3[2],d4[2]; // 左上到右上，左上到右下，左下到右上，左下到右下
    int dl[2],dr[2]; // 左上到左下 右上到右下
    int l1[2],l2[2],r1[2],r2[2];
    int dans,dcnt; 
}
struct segment{
    int l,r;
    data d;
}t[];
int len;
int st[],to[],next[];
int fa[][],dep[],size[],q[],seq[],rank[],a[],clr[][];
int dd[],head[];

void addedge(int x,int y)
{
     len++; to[len]=y; next[len]=st[x]; st[x]=len;
     len++; to[len]=x; next[len]=st[y]; st[y]=len;
}
int go_up(int x,int d)
{
    for (int i=17;i>=0;i--)
        if (d&(1<<i)) x=fa[x][i];
    return x;
}
int LCA(int x,int y)
{
    if (dep[x]>dep[y]) x=go_up(x,dep[x]-dep[y]);
       else y=go_up(y,dep[y]-dep[x]);
    if (x==y) return x;
    for (int i=17;i>=0;i--)
        if (fa[x][i]!=fa[y][i])
        {
            x=fa[x][i]; y=fa[y][i];
        }
    return fa[x][0];
}
data merge(data a,data b)
{
     
}
void build(int i,int l,int r)
{
     int mid=(l+r)>>1;
     
}
void modify_num()
{
     
}
void modify_clr()
{
     
}
void fill()
{
     
}
void query()
{
     
}
void work()
{
     
}

int main()
{
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    n=read();
    for (int i=1;i<n;i++)
    {
        x=read(); y=read();
        addedge(x,y);
    }
    vis[1]=1; q[1]=1; fa[1][0]=0; dep[1]=0;
    int head=0,tail=1;
    while (head!=tail)
    {
        head++; int now=q[head];
        for (int i=st[now];i;i=next[i])
            if (!vis[to[i]])
            {
                dep[to[i]]=dep[now]+1; fa[to[i]][0]=now;
                vis[to[i]=1; tail++; q[tail]=to[i];
            }
    }
    size[0]=0;
    for (int i=n;i>=1;i--)
    {
        size[q[i]]=1; dd[q[i]]=0;
        for (int j=st[q[i]];j;j=next[j])
            if(dep[q[i]]<dep[to[j]])
            {
                size[q[i]]+=size[to[j]];
                if (size[to[j]]>size[dd[q[i]]]) dd[q[i]]=to[j];
            }
    }
    int j=0;k=0;
    for (int i=1;i<=n;i++)
    {
        k=q[i];
        while (k)
        {
            j++; vis[k]=0; seq[j]=k; head[k]=q[i]; k=dd[k];
        }
    }
    for (int i=1;i<=n;i++) rank[seq[i]]=i;
    for (int j=1;j<=17;j++)
        for (int i=1;i<=n;i++)
            if (fa[i][j-1]==0) fa[i][j]=0;
               else fa[i][j]=fa[fa[i][j-1]][j-1];
    build(1,1,n);
    m=read();
    while (m--)
    {
        
    }
    return 0;
}
