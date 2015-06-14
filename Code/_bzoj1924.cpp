#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#include<ctime>
#include<vector>
#include<queue>
#include<algorithm>
#include<map>
#define inf 1000000000
#define ll long long 
using namespace std;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int xx[8]={0,0,1,1,1,-1,-1,-1},yy[8]={1,-1,0,1,-1,0,1,-1};
int K,n,m,cnt,ind,scc,top,ans;
int last[100005],last2[100005];
int x[100005],y[100005],opt[100005];
int bl[100005],low[100005],dfn[100005],num[100005],q[100005];
int deep[100005];
bool mark[100005];
vector<int> a[1000005],b[1000005];
map<int,int> mp[1000005];
struct edge{
	int to,next;
}e[1000005],ed[1000005];
void insert(int u,int v)
{
	if(u==v)return;
	e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;
}
void insert2(int u,int v)
{
	ed[++cnt].to=v;ed[cnt].next=last2[u];last2[u]=cnt;
}
void build()
{
	for(int i=1;i<=n;i++)
	{
		int x=0,t=a[i].size();
		for(int j=0;j<t;j++)
			if(opt[a[i][j]]==1){x=a[i][j];break;}
		for(int j=0;j<t;j++)
		{
			insert(x,a[i][j]);
			if(opt[a[i][j]]==1)insert(a[i][j],x);
		}
	}
	for(int i=1;i<=m;i++)
	{
		int x=0,t=b[i].size();
		for(int j=0;j<t;j++)
			if(opt[b[i][j]]==2){x=b[i][j];break;}
		for(int j=0;j<t;j++)
		{
			insert(x,b[i][j]);
			if(opt[b[i][j]]==2)insert(b[i][j],x);
		}
	}
	for(int i=1;i<=K;i++)
		if(opt[i]==3)
			for(int k=0;k<8;k++)
			{
				int t=mp[x[i]+xx[k]][y[i]+yy[k]];
				if(t)insert(i,t);
			}
}
void tarjan(int x)
{
	low[x]=dfn[x]=++ind;
	q[++top]=x;mark[x]=1;
	for(int i=last[x];i;i=e[i].next)
		if(!dfn[e[i].to])
		{
			tarjan(e[i].to);
			low[x]=min(low[x],low[e[i].to]);
		}
		else if(mark[e[i].to])
			low[x]=min(low[x],dfn[e[i].to]);
	if(low[x]==dfn[x])
	{
		int now=0;scc++;
		while(now!=x)
		{
			now=q[top--];mark[now]=0;
			bl[now]=scc;num[scc]++;
		}
	}
}
void rebuild()
{
	cnt=0;
	for(int x=1;x<=K;x++)
	{
		for(int i=last[x];i;i=e[i].next)
			if(bl[x]!=bl[e[i].to])
				insert2(bl[x],bl[e[i].to]);
	}
}
void dp(int x)
{
	mark[x]=1;
	for(int i=last2[x];i;i=ed[i].next)
	{
		if(!mark[ed[i].to])dp(ed[i].to);
		deep[x]=max(deep[x],deep[ed[i].to]);
	}
	deep[x]+=num[x];
	ans=max(deep[x],ans);
}
int main()
{
	K=read();n=read();m=read();
	for(int i=1;i<=K;i++)
	{
		x[i]=read(),y[i]=read(),opt[i]=read();
		mp[x[i]][y[i]]=i;
		a[x[i]].push_back(i);
		b[y[i]].push_back(i);
	}
	build();
	for(int i=1;i<=K;i++)
		if(!dfn[i])tarjan(i);
	rebuild();
	for(int i=1;i<=scc;i++)
		if(!mark[i])dp(i);
	printf("%d\n",ans);
	return 0;
}
