#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define inf 1000000000
#define ll long long
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,cnt,sum,rt,mxdeep;
bool vis[200005];
int t[200005],mx[100005],fa[100005],size[100005],deep[100005],dis[100005];
ll ans,g[200005][2],f[200005][2];
struct edge{int to,next,v;}e[200005];int last[100005];
void insert(int u,int v,int w)
{
	e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;e[cnt].v=w;
	e[++cnt].to=u;e[cnt].next=last[v];last[v]=cnt;e[cnt].v=w;
}
void getroot(int x,int fa)
{
	size[x]=1;mx[x]=0;
	for(int i=last[x];i;i=e[i].next)
		if(e[i].to!=fa&&!vis[e[i].to])
		{
			getroot(e[i].to,x);
			size[x]+=size[e[i].to];
			mx[x]=max(mx[x],size[e[i].to]);
		}
	mx[x]=max(mx[x],sum-size[x]);
	if(mx[x]<mx[rt])rt=x;
}
void dfs(int x,int fa)
{
	mxdeep=max(mxdeep,deep[x]);
	if(t[dis[x]])f[dis[x]][1]++;
	else f[dis[x]][0]++;
	t[dis[x]]++;
	for(int i=last[x];i;i=e[i].next)
		if(e[i].to!=fa&&!vis[e[i].to])
		{
			deep[e[i].to]=deep[x]+1;
			dis[e[i].to]=dis[x]+e[i].v;
			dfs(e[i].to,x);
		}
	t[dis[x]]--;
}
void cal(int x)
{
	int mx=0;
	vis[x]=1;g[n][0]=1;
	for(int i=last[x];i;i=e[i].next)
		if(!vis[e[i].to])
		{
			dis[e[i].to]=n+e[i].v;
			deep[e[i].to]=1;
			mxdeep=1;dfs(e[i].to,0);mx=max(mx,mxdeep);
			ans+=(g[n][0]-1)*f[n][0];
			for(int j=-mxdeep;j<=mxdeep;j++)
				ans+=g[n-j][1]*f[n+j][1]+g[n-j][0]*f[n+j][1]+g[n-j][1]*f[n+j][0];
			for(int j=n-mxdeep;j<=n+mxdeep;j++)
			{
				g[j][0]+=f[j][0];
				g[j][1]+=f[j][1];
				f[j][0]=f[j][1]=0;
			}
		}
	for(int i=n-mx;i<=n+mx;i++)
		g[i][0]=g[i][1]=0;
	for(int i=last[x];i;i=e[i].next)
		if(!vis[e[i].to])
		{
			sum=size[e[i].to];
			rt=0;
			getroot(e[i].to,0);
			cal(rt);
		}
}
int main()
{
	n=read();
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read(),w=read();
		if(!w)w=-1;
		insert(u,v,w);
	}
	sum=mx[0]=n;
	getroot(1,0);
	cal(rt);
	printf("%lld",ans);
	return 0;
}
