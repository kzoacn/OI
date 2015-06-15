#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define rad 100000000
#define inf 1000000000
#define ll long long 
#define eps 1e-10
#define pa pair<ll,int>
#define p(x,y) (x-1)*n+y
using namespace std;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,A,B,cnt,tot;
int last[25],d[25];
double a[405][405],p[25];
vector<int> e[25];
void build(int x,int y)
{

	
		
	a[p(x,y)][p(x,y)]--;
    for(unsigned int i=0;i<e[x].size();i++)
        for(unsigned int j=0;j<e[y].size();j++)
        {
            int tx=e[x][i],ty=e[y][j];
			int t1=p(x,y),t2=p(tx,ty);
            if(tx!=ty)
            {
                if(tx==x&&ty==y)a[t1][t2]+=p[tx]*p[ty];
                else if(tx==x)a[t1][t2]+=p[tx]*(1-p[ty])/d[ty];
                else if(ty==y)a[t1][t2]+=p[ty]*(1-p[tx])/d[tx];
                else a[t1][t2]+=(1-p[tx])*(1-p[ty])/d[tx]/d[ty];
            }
        }
}
void gauss()
{

	for(int i=1;i<=tot;i++)
	for(int j=1;j<=tot+1;j++)
		printf("%.2lf%c",a[i][j]," \n"[j==tot+1]);
	
    int now=1;
    for(int i=1;i<=tot;i++)
    {
        int j;
        for(j=now;!a[j][now]&&j<=tot;j++);
        for(int k=1;k<=tot+1;k++)swap(a[now][k],a[j][k]);
        for(int j=1;j<=tot;j++)
            if(j!=now)
            {
                double t=a[j][now]/a[now][now];
                for(int k=1;k<=tot+1;k++)
                    a[j][k]-=t*a[now][k];
            }
        now++;
    }
}
int main()
{
	freopen("bzoj3270.in","r",stdin);
    n=read();m=read();A=read();B=read();
    tot=n*n;
    a[p(A,B)][tot+1]=-1;
    for(int i=1;i<=n;i++)e[i].push_back(i);
    for(int i=1;i<=m;i++)
    {
        int u=read(),v=read();
        d[u]++;d[v]++;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for(int i=1;i<=n;i++)scanf("%lf",&p[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            build(i,j);
    gauss();    
    for(int i=1;i<=n;i++)
    {
		int t=p(i,i);
        printf("%.6lf",a[t][tot+1]/a[t][t]);
        if(i!=n)printf(" ");
    }
    return 0;
}
