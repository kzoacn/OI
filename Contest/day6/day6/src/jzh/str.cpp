#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int N = 55;
int n;
long long m;
long long ci[N];
bool xu[N],fan[N];
bool sc[N];
long long CalcLing(int all,int x)
{
	int i;
	bool permit=1;
	for(i=x+1;i<=all;i++)
	{
		if(xu[i]<sc[i])
		{
			permit=1;
			break;
		}
		if(xu[i]>sc[i])
		{
			permit=0;
			break;
		}
	}
	long long res=0;
	if(permit)
		res++;
	for(i=2;i<=x;i++)
	{
		if(xu[i]==0)
			res+=ci[x-i];
	}
	return res;
}
long long CalcYi(int all,int x,bool permit)
{
	int i;
	for(i=x+1;i<=all;i++)
	{
		if(fan[i]>sc[i])
		{
			permit=1;
			break;
		}
		if(fan[i]<sc[i])
		{
			permit=0;
			break;
		}
	}
	long long res=0;
	if(permit)
		res++;
	for(i=2;i<=x;i++)
	{
		if(fan[i]==1)
			res+=ci[x-i];
	}
	return res;
}
long long Calc(int all,int x,bool permit)
{
	int i;
	if(x==0)
	{
		if(sc[1]==0)
		{
			for(i=1;i<=all;i++)
			{
				if(sc[i]>xu[i])
					return 1;
				if(sc[i]<xu[i])
					return 0;
			}
			return 1;
		}
		else
		{
			for(i=1;i<=all;i++)
			{
				if(sc[i]<fan[i])
					return 1;
				if(sc[i]>fan[i])
					return 0;
			}
			if(permit)
				return 1;
			else
				return 0;
		}
	}
	long long res=CalcLing(all,x)+CalcYi(all,x,permit);
	return res;
}
void Make(int x,long long y,bool permit)
{
	if(x==n/2)
	{
		int i;
		for(i=1;i<=x;i++)
			fan[i]=xu[i]^1;
	}
	if(x==0)
	{
		int i;
		for(i=n/2;i>=1;i--)
			printf("%d",sc[i]);
		printf("\n");
		return;
	}
	sc[x]=0;
	long long now=Calc(n/2,x-1,permit);
	if(now>y)
		Make(x-1,y,permit);
	else
	{
		sc[x]=1;
		Make(x-1,y-now,permit);
	}
}
bool Dfs(int x,int wei,long long has)
{
	if(x==(n+1)/2)
	{
		if(n&1)
		{
			long long now;
			xu[x]=0;
			now=has*2+2;
			if(m<now)
			{
				int i;
				for(i=1;i<=x;i++)
					printf("%d",xu[i]);
				Make(x-1,m,1);
				return 1;
			}
			m-=now;
			xu[x]=1;
			now=has*2+1;
			if(m<now)
			{
				int i;
				for(i=1;i<=x;i++)
					printf("%d",xu[i]);
				Make(x-1,m,0);
				return 1;
			}
			m-=now;
			return 0;
		}
		else
		{
			long long now;
			xu[x]=0;
			now=(has+ci[wei]+1)*2;
			if(m<now)
			{
				int i;
				for(i=1;i<=x;i++)
					printf("%d",xu[i]);
				Make(x,m,1);
				return 1;
			}
			m-=now;
			xu[x]=1;
			now=has*2+2;
			if(m<now)
			{
				int i;
				for(i=1;i<=x;i++)
					printf("%d",xu[i]);
				Make(x,m,1);
				return 1;
			}
			m-=now;
			return 0;
		}
	}
	if(x==1)
	{
		xu[x]=0;
		if(Dfs(x+1,wei-1,has))
			return 1;
		return 0;
	}
	else
	{
		xu[x]=0;
		if(Dfs(x+1,wei-1,has+ci[wei]))
			return 1;
		xu[x]=1;
		return Dfs(x+1,wei-1,has);
	}
}
int main()
{
	freopen("str.in","r",stdin);
	freopen("str.out","w",stdout);
	cin>>n>>m;
	int i;
	ci[0]=1;
	for(i=1;i<=n;i++)
		ci[i]=ci[i-1]*2;
	if(!Dfs(1,n/2-1,0))
		printf("-1\n");
	return 0;
}