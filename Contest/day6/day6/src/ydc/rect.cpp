#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define mod 10007
#define maxn 1010
using namespace std;
typedef long long LL;
char map[maxn][maxn];
int n,sum1[maxn][maxn],sum2[maxn][maxn],sum3[maxn][maxn],sum4[maxn][maxn];
int cnt1[maxn][maxn],cnt2[maxn][maxn];
void read()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%s",map[i]+1);
}
void prepare()
{
	static int stack[maxn],h[maxn];
	//sum1以(i,j)为左下角的矩形数 
	for(int i=1;i<=n;++i)
	{
		int area=0,top=0;
		stack[0]=n+1;
		for(int j=n;j>=1;--j)
		{
			h[j]=map[i][j]=='B'?0:h[j]+1;
			if(top==0)
				area=h[j],stack[++top]=j;
			else
			{
				area+=h[j];
				while(top&&h[stack[top]]>=h[j])
					area=area-(stack[top-1]-stack[top])*(h[stack[top]]-h[j]),--top;
				stack[++top]=j;
			}
			sum1[i][j]=max(0,area%mod-1);
		}
	}
	memset(h,0,sizeof(h));
	//sum2以(i,j)为右上角的矩形数 
	for(int i=n;i>=1;--i)
	{
		int area=0,top=0;
		stack[0]=0;
		for(int j=1;j<=n;++j)
		{
			h[j]=map[i][j]=='B'?0:h[j]+1;
			if(top==0)
				area=h[j],stack[++top]=j;
			else
			{
				area+=h[j];
				while(top&&h[stack[top]]>=h[j])
					area=area-(stack[top]-stack[top-1])*(h[stack[top]]-h[j]),--top;
				stack[++top]=j;
			}
			sum2[i][j]=max(0,area%mod-1);
		}
	}
	memset(h,0,sizeof(h));
	//sum3以(i,j)为右下角 
	for(int i=1;i<=n;++i)
	{
		int area=0,top=0;
		stack[0]=0;
		for(int j=1;j<=n;++j)
		{
			h[j]=map[i][j]=='B'?0:h[j]+1;
			if(top==0)
				area=h[j],stack[++top]=j;
			else
			{
			 	area+=h[j];
			 	while(top&&h[stack[top]]>=h[j])
				 	area=area-(stack[top]-stack[top-1])*(h[stack[top]]-h[j]),--top;
			 	stack[++top]=j;
		 	}
		 	sum3[i][j]=max(0,area%mod-1);
		}
	}
	memset(h,0,sizeof(h));
	//sum4以(i,j)为左上角 
	for(int i=n;i>=1;--i)
	{
		int area=0,top=0;
		stack[0]=n+1;
		for(int j=n;j>=1;--j)
		{
			h[j]=map[i][j]=='B'?0:h[j]+1;
			if(top==0)
				area=h[j],stack[++top]=j;
			else
			{
			 	area+=h[j];
			 	while(top&&h[stack[top]]>=h[j])
				 	area=area-(stack[top-1]-stack[top])*(h[stack[top]]-h[j]),--top;
			 	stack[++top]=j;
		 	}
		 	sum4[i][j]=max(0,area%mod-1);
		}
	}
}
int calc1(int a,int b,int c,int d)
{
 	return (cnt1[c][d]-cnt1[a-1][d]-cnt1[c][b-1]+cnt1[a-1][b-1]+mod+mod)%mod;
}
int calc2(int a,int b,int c,int d)
{
 	return (cnt2[c][d]-cnt2[a-1][d]-cnt2[c][b-1]+cnt2[a-1][b-1]+mod+mod)%mod;
}
void work()
{
	static int F[maxn];
	int ans=0;
	for(int j=n;j>=1;--j)
	{
		int s=0;
		for(int i=1;i<=n;++i)
		{
			s=s+sum2[i][j];
			F[j]=F[j]+sum1[i][j];
		}
		s%=mod,F[j]%=mod;
		ans=(ans+s*F[j+1])%mod;
		F[j]=(F[j]+F[j+1])%mod;
	}
	for(int i=1;i<=n;++i)
	{
		int s=0;
		F[i]=0;
		for(int j=n;j>=1;--j)
		{
			s=s+sum2[i][j];
			F[i]=F[i]+sum1[i][j];
		}
		s%=mod,F[i]%=mod;
		ans=(ans+s*F[i-1])%mod;
		F[i]=(F[i]+F[i-1])%mod;
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			cnt1[i][j]=(cnt1[i-1][j]+cnt1[i][j-1]-cnt1[i-1][j-1]+sum2[i][j]+mod)%mod;
			cnt2[i][j]=(cnt2[i-1][j]+cnt2[i][j-1]-cnt2[i-1][j-1]+sum4[i][j]+mod)%mod;
		}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			ans=(ans-sum1[i][j]*calc1(i+1,1,n,j-1)%mod+mod)%mod;
			ans=(ans-sum3[i][j]*calc2(i+1,j+1,n,n)%mod+mod)%mod;
		}
	printf("%d\n",ans);
}
int main()
{
	freopen("rect.in","r",stdin);
	freopen("rect.out","w",stdout);
	read();
	prepare();
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
