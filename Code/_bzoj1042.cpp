#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#include<ctime>
#include<queue>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;
ll ans,f[100005];
int T;
int c[5],d[5];
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
void dfs(int x,int k,int sum)
{
	if(sum<0)return;
	if(x==5)
	{
		if(k&1)ans-=f[sum];
		else ans+=f[sum];
		return;
	}
    dfs(x+1,k+1,sum-(d[x]+1)*c[x]);
	dfs(x+1,k,sum);
}
int main()
{
	for(int i=1;i<=4;i++)c[i]=read();
	T=read();
	f[0]=1;
	for(int i=1;i<=4;i++)
		for(int j=c[i];j<=100000;j++)
			f[j]+=f[j-c[i]];
	for(int i=1;i<=T;i++)
	{
		for(int k=1;k<=4;k++)d[k]=read();
		int x=read();
		ans=0;
		dfs(1,0,x);
		printf("%lld\n",ans);
	}
	return 0;
}
