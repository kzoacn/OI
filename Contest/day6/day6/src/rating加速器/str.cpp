#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#include<map>
#include<set>
#include<stack>
#include<string>
#include<cmath>
#include<cctype>
#include<ctime>
#include<bitset>
using namespace std;
const int maxlongint=2147483647;
const int inf=1000000000;
long long dp[55][4];
int p[55],rev[20][200010];
int main()
{
	freopen("str.in","r",stdin);
	freopen("str.out","w",stdout);
	int n,n1,n2;
	long long k;
	cin>>n>>k;
	k++;
	dp[0][0]=dp[0][1]=dp[0][2]=dp[0][3]=dp[1][2]=dp[1][3]=1;
	dp[1][0]=dp[1][1]=2;
	for(n1=2;n1<=n;n1++)
	{
		dp[n1][0]=dp[n1-1][0]*2;
		dp[n1][1]=dp[n1-2][1]*2+dp[n1-2][0];
		dp[n1][2]=dp[n1-2][2]*2+dp[n1-2][0];
		dp[n1][3]=dp[n1-2][1]+dp[n1-2][2];
	}
	if(k>dp[n][3])
	{
		cout<<-1;
		return 0;
	}
	p[1]=0;
	long long x=0,y=n-4;
	for(n2=2;n2<=n/2;n2++)
	{
		if(dp[y][1]+dp[y][2]+dp[y][0]*(2+x*2)>=k)
		{
			p[n2]=0;
			x=x*2+2;
		}
		else
		{
			k-=dp[y][1]+dp[y][2]+dp[y][0]*(2+x*2);
			p[n2]=1;
			x=x*2;
		}
		y-=2;
	}
	long long now=0,fnow=0,j,z,f,g,re,nnow,nfnow,nynow,nyfnow;
	for(n2=1;n2<=n/2;n2++)
	{
		now=now*2+p[n2];
	}
	for(n2=n/2;n2>=1;n2--)
	{
		fnow=fnow*2+p[n2];
	}
	x=n/2+n%2,y=n/2;
	for(int i=0;i<=15;i++)
		for(int j=0;j<(1<<i);j++)
		{
			int p=0;
			for(int k=0;k<i;k++)
				if(j&(1<<k))
					p=p*2+1;
				else
					p=p*2;
			rev[i][j]=p;
		}
	int nowans=0;
	for(int i=0;i<(1<<x);i++)
	{
		j=x/2,z=x-x/2,f=i&((1<<z)-1),g=(i^f)>>z;
		re=rev[j][g]|(rev[z][f]<<j);
		nnow=(now<<x)+i,nfnow=(re<<y)+fnow,nynow=((1<<n)-1)^nnow,nyfnow=((1<<n)-1)^nfnow;
	//	cout<<nnow<<' '<<nfnow<<' '<<nynow<<' '<<nyfnow<<endl;
		if(nnow<=nfnow&&nnow<=nynow&&nnow<=nyfnow)
		{
			nowans++;
			if(nowans==k)
			{
				for(n1=1;n1<=y;n1++)
					printf("%d",p[n1]);
				for(n1=x-1;n1>=0;n1--)
				{
					if(i&(1<<n1))
						printf("1");
					else
						printf("0");
				}
				return 0;
			}
		}
	}
}
