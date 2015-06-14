#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
   
const int maxn=10001,maxm=1000001;
const double eps=1e-9;
int n,m,s,t,i,x,y,stack[maxn+1],top,flag[maxn],low[maxn],rea[maxn],lab[maxn],bel[maxn],cnt[maxn],tim,tot,size[maxn],scc[maxn][101];
struct data
{
    int v;
    data *next;
} *first[maxn],pool[maxm],*tp=pool;
double mat[101][102],ans[maxn];
bool nosol;
   
void tarjan(int x)
{
    flag[x]=1;
    rea[x]=low[x]=tim++;
    stack[++top]=x;
    for (data *i=first[x]; i; i=i->next)
    {
        if (!flag[i->v])
            tarjan(i->v);
        if (flag[i->v]<2)
            low[x]=min(low[x],low[i->v]);
    }
    if (rea[x]==low[x])
    {
        ++tot;
        while (stack[top+1]!=x)
        {
            scc[tot][++scc[tot][0]]=stack[top];
            bel[stack[top]]=tot;
            lab[stack[top]]=++size[tot];
            flag[stack[top--]]=2;
        }
    }
}
   
void elimination(int n)
{
    for (int i=1; i<=n; ++i)
    {
        int k=i;
        for (int j=i+1; j<=n; ++j)
            if (fabs(mat[j][i])>fabs(mat[k][i]))
                k=j;
        for (int j=1; j<=n+1; ++j)
            swap(mat[i][j],mat[k][j]);
        if (fabs(mat[i][i])<=eps)
            continue;
        for (int j=n+1; j>=i; --j)
            mat[i][j]/=mat[i][i];
        for (int j=1; j<=n; ++j)
            if (i!=j)
                for (int k=n+1; k>=i; --k)
                    mat[j][k]-=mat[i][k]*mat[j][i];
    }
}
   
void dfs(int x)
{
    if (flag[x])
        return;
    if (bel[t]==x)
        flag[x]=2;
    else
        flag[x]=1;
    for (int i=1; i<=scc[x][0]; ++i)
        for (data *j=first[scc[x][i]]; j; j=j->next)
        {
            dfs(bel[j->v]);
            if (flag[bel[j->v]]==2)
                flag[x]=2;
        }
    if (flag[x]!=2)
    {
        nosol=true;
        return;
    }
    memset(mat,0,sizeof(mat));
    for (int i=1; i<=scc[x][0]; ++i)
    {
        mat[lab[scc[x][i]]][lab[scc[x][i]]]=1;
        if (scc[x][i]!=t)
            for (data *j=first[scc[x][i]]; j; j=j->next)
                if (bel[j->v]==x)
                {
                    mat[lab[scc[x][i]]][lab[j->v]]+=static_cast<double>(-1)/cnt[scc[x][i]];
                    mat[lab[scc[x][i]]][size[x]+1]+=static_cast<double>(1)/cnt[scc[x][i]];
                }
                else
                    mat[lab[scc[x][i]]][size[x]+1]+=(ans[j->v]+1)/cnt[scc[x][i]];
    }
    elimination(size[x]);
    for (int i=1; i<=scc[x][0]; ++i)
        ans[scc[x][i]]=mat[lab[scc[x][i]]][size[x]+1];
}
   
int main()
{
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for (i=1; i<=m; ++i)
    {
        scanf("%d%d",&x,&y);
        tp->v=y;
        tp->next=first[x];
        first[x]=tp++;
        ++cnt[x];
    }
    tarjan(s);
    memset(flag,0,sizeof(flag));
    dfs(bel[s]);
    if (nosol)
    {
        printf("INF\n");
        return 0;
    }
    printf("%.3f\n",ans[s]);
    return 0;
}
