#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<set>
#include<stack>
#include<cstdlib>
#include<string>
#include<bitset>
#include<map>
#define INF 1000000000
#define N 1005
#define fi first
#define se second
#define P 10007
#define debug(x) cout<<#x<<"="<<x<<endl
#define MP(x,y) make_pair(x,y)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
void inline upd(int& x,int y)
{
	x+=y;
	if(x>=P) x%=P; 
}

int dp1[N][N],s1[N][N],dp2[N][N],s2[N][N],dp3[N][N],s3[N][N],dp4[N][N],s4[N][N];
char mp1[N][N],mp2[N][N],mp3[N][N],mp4[N][N];
int tp,dn[N];
pii stk[N];
int main()
{
	int n,i,j,x,now;
	freopen("rect.in","r",stdin);
	freopen("rect.out","w",stdout);
	cin>>n;
	for(i=1;i<=n;i++)
	{
		scanf("%s",mp1[i]+1);
		memcpy(mp2[n-i+1],mp1[i],sizeof(mp1[i]));
		memcpy(mp3[i],mp1[i],sizeof(mp1[i]));
		memcpy(mp4[n-i+1],mp1[i],sizeof(mp1[i]));
		reverse(mp2[n-i+1]+1,mp2[n-i+1]+n+1);
		reverse(mp3[i]+1,mp3[i]+n+1);
	}
	memset(dn,0,sizeof(dn));
	for(i=1;i<=n;i++)
	{
		tp=1;
		stk[1]=MP(i+1,0);
		now=0;
		for(j=1;j<=n;j++)
		{
			if(mp1[i][j]=='B')
			{
				while(tp>1)
					tp--;
				dp1[i][j]=0;
				s1[i][j]=(s1[i-1][j]+s1[i][j-1]-s1[i-1][j-1]+dp1[i][j]+P)%P;
				dn[j]=i;
				now=0;
			}
			else
			{
				x=j;
				while(dn[j]>=stk[tp].fi)
				{
					//debug(now);
					//debug(i);
					//debug(j);
					//debug(stk[tp].fi);
					//debug(stk[tp].se);
					now=(now-(j-stk[tp].se)*(stk[tp-1].fi-stk[tp].fi)%P+P)%P;
					x=stk[tp].se;
					tp--;
				}
				if(dn[j]+1!=stk[tp].fi)
				{
					tp++;
					stk[tp].fi=dn[j]+1;
					stk[tp].se=x;
					upd(now,(j-x)*(stk[tp-1].fi-stk[tp].fi)%P);
				}
				upd(now,(i-stk[tp].fi+1));
				dp1[i][j]=(now-1+P)%P;
				s1[i][j]=(s1[i-1][j]+s1[i][j-1]-s1[i-1][j-1]+dp1[i][j]+P)%P;
			}
		}
	}
	memset(dn,0,sizeof(dn));
	for(i=1;i<=n;i++)
	{
		tp=1;
		stk[1]=MP(i+1,0);
		now=0;
		for(j=1;j<=n;j++)
		{
			if(mp2[i][j]=='B')
			{
				while(tp>1)
					tp--;
				dp2[i][j]=0;
				s2[i][j]=(s2[i-1][j]+s2[i][j-1]-s2[i-1][j-1]+dp2[i][j]+P)%P;
				dn[j]=i;
				now=0;
			}
			else
			{
				x=j;
				while(dn[j]>=stk[tp].fi)
				{
					now=(now-(j-stk[tp].se)*(stk[tp-1].fi-stk[tp].fi)%P+P)%P;
					x=stk[tp].se;
					tp--;
				}
				if(dn[j]+1!=stk[tp].fi)
				{
					tp++;
					stk[tp].fi=dn[j]+1;
					stk[tp].se=x;
					upd(now,(j-x)*(stk[tp-1].fi-stk[tp].fi)%P);
				}
				upd(now,(i-stk[tp].fi+1));
				dp2[i][j]=(now-1+P)%P;
				s2[i][j]=(s2[i-1][j]+s2[i][j-1]-s2[i-1][j-1]+dp2[i][j]+P)%P;
			}
		}
	}
	memset(dn,0,sizeof(dn));
	for(i=1;i<=n;i++)
	{
		tp=1;
		stk[1]=MP(i+1,0);
		now=0;
		for(j=1;j<=n;j++)
		{
			if(mp3[i][j]=='B')
			{
				while(tp>1)
					tp--;
				dp3[i][j]=0;
				//s3[i][j]=(s3[i-1][j]+s3[i][j-1]-s3[i-1][j-1]+dp3[i][j]+P)%P;
				dn[j]=i;
				now=0;
			}
			else
			{
				x=j;
				while(dn[j]>=stk[tp].fi)
				{
					now=(now-(j-stk[tp].se)*(stk[tp-1].fi-stk[tp].fi)%P+P)%P;
					x=stk[tp].se;
					tp--;
					
				}
				if(dn[j]+1!=stk[tp].fi)
				{
					tp++;
					stk[tp].fi=dn[j]+1;
					stk[tp].se=x;
					upd(now,(j-x)*(stk[tp-1].fi-stk[tp].fi)%P);
				}
				upd(now,(i-stk[tp].fi+1));
				dp3[i][j]=(now-1+P)%P;
				//s3[i][j]=(s3[i-1][j]+s3[i][j-1]-s3[i-1][j-1]+dp3[i][j]+P)%P;
			}
		}
	}
	memset(dn,0,sizeof(dn));
	for(i=1;i<=n;i++)
	{
		tp=1;
		stk[1]=MP(i+1,0);
		now=0;
		for(j=1;j<=n;j++)
		{
			if(mp4[i][j]=='B')
			{
				while(tp>1)
					tp--;
				dp4[i][j]=0;
				s4[i][j]=(s4[i-1][j]+s4[i][j-1]-s4[i-1][j-1]+dp4[i][j]+P)%P;
				dn[j]=i;
				now=0;
			}
			else
			{
				x=j;
				while(dn[j]>=stk[tp].fi)
				{
					now=(now-(j-stk[tp].se)*(stk[tp-1].fi-stk[tp].fi)%P+P)%P;
					x=stk[tp].se;
					tp--;
				}
				if(dn[j]+1!=stk[tp].fi)
				{
					tp++;
					stk[tp].fi=dn[j]+1;
					stk[tp].se=x;
					upd(now,(j-x)*(stk[tp-1].fi-stk[tp].fi)%P);
				}
				upd(now,(i-stk[tp].fi+1));
				dp4[i][j]=(now-1+P)%P;
				s4[i][j]=(s4[i-1][j]+s4[i][j-1]-s4[i-1][j-1]+dp4[i][j]+P)%P;
			}
		}
	}
	/*
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			printf("%d ",dp1[i][j]);
		cout<<endl;
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			printf("%d ",dp4[n-i+1][j]);
		cout<<endl;
	}*/
	int ans=0;
	for(i=1;i<n;i++)
	{
		ans=(ans+(s1[i][n]-s1[i-1][n]+P)*s2[n-i][n])%P;
		ans=(ans+(s1[n][i]-s1[n][i-1]+P)*s2[n][n-i])%P;
	}
	for(i=1;i<n;i++)
		for(j=1;j<n;j++)
		{
			ans=(ans-dp1[i][j]*s2[n-i][n-j]%P+P)%P;
			ans=(ans-dp3[i][j]*s4[n-i][n-j]%P+P)%P;
		}
	cout<<ans<<endl;
	return 0;
}
// davidlee1999WTK 2015/
// srO myk Orz
//ios::sync_with_stdio(false);
/*
3
CCB
CCB
CBB

5
BBBCC
BBCCC
BCCCC
BBCCC
CCCCC

5
WWWCC
WWCCC
WCCCW
WWCCC
CCCCC

5
WWWCC
WWCCC
WCCCC
WWCCC
CCCCC

5
BCCBB
BBCBB
BCCBB
BBBBB
CCBBB
*/
