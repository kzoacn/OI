#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#define N 1000001
#define ll long long 
using namespace std;
int n,cnt;ll ans,answer;
int v[N],fa[N],head[N],to[N],next[N],ez[N],bh[N];
ll dp[N][2],f[N][4];
bool mark[N];
void Ins(int a,int b)
{cnt++;to[cnt]=b;next[cnt]=head[a];head[a]=cnt;}
void init()
{
	int i,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{scanf("%d%d",&v[i],&k);Ins(k,i);fa[i]=k;}
}
void treedp(int x)
{
	dp[x][1]=v[x];dp[x][0]=0;
	mark[x]=1;
	int i=head[x];
	while(i>0)
	{
		treedp(to[i]);
		dp[x][0]+=max(dp[to[i]][0],dp[to[i]][1]);
		dp[x][1]+=dp[to[i]][0];
		i=next[i];
	}
}
void finaldp()
{
	int i,k;
	ans=0;
	f[1][1]=0;f[1][2]=0;
	f[1][0]=dp[bh[1]][1];
	f[1][3]=dp[bh[1]][0];
	for(i=2;i<=bh[0];i++)
	{
		k=bh[i];
		f[i][0]=f[i-1][1]+dp[k][1];
		f[i][1]=max(f[i-1][0],f[i-1][1])+dp[k][0];
		f[i][2]=f[i-1][3]+dp[k][1];
		f[i][3]=max(f[i-1][2],f[i-1][3])+dp[k][0];
	}
	ans=max(f[bh[0]][1],max(f[bh[0]][2],f[bh[0]][3]));
}
void solve()
{
	int i,k,j,now;
	for(i=1;i<=n;i++)
	{
	if(mark[i])continue;
	bh[0]=0;
	k=i;
	while(!mark[k])
	{
		mark[k]=1;
		k=fa[k];
		ez[fa[k]]=k;
	}
	now=k;
	while(1)
	{
		i=head[k];
		dp[k][1]=v[k];
		while(i>0)
		{
			if(to[i]!=ez[k])
			{treedp(to[i]);
	    	dp[k][0]+=max(dp[to[i]][0],dp[to[i]][1]);
	    	dp[k][1]+=dp[to[i]][0];}
	     	i=next[i];
		}
		bh[0]++;bh[bh[0]]=k;
		k=fa[k];
		if(k==now)
		break;
	}
	finaldp();
	answer+=ans;
    }
	printf("%I64d\n",answer);
}
int main()
{
	init();
	solve();
	return 0;
}
