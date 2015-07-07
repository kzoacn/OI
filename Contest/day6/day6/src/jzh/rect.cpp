#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int N = 1005;
const int Mod = 10007;
int n;
bool map[N][N];
int up[N][N],down[N][N];
int lu[N][N],ld[N][N],ru[N][N],rd[N][N];
int slu[N][N],sld[N][N],sru[N][N],srd[N][N];
int zhan[N],tot[N],cc,nv;
bool getbool()
{
	char ch=getchar();
	while(ch!='B' && ch!='C')
		ch=getchar();
	return(ch=='C');
}
void GetData()
{
	int i,j;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			map[i][j]=getbool();
	}
}
void MakeLine()
{
	int i,j;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(map[i][j])
				up[i][j]=up[i-1][j]+1;
		}
	}
	for(i=n;i>=1;i--)
	{
		for(j=1;j<=n;j++)
		{
			if(map[i][j])
				down[i][j]=down[i+1][j]+1;
		}
	}
}
void Clear()
{
	cc=0;
	nv=0;
}
int Add(int x)
{
	int cnt=1;
	while(cc && zhan[cc]>=x)
	{
		cnt+=tot[cc];
		nv-=tot[cc]*zhan[cc];
		cc--;
	}
	cc++;
	zhan[cc]=x;
	tot[cc]=cnt;
	nv+=x*cnt;
	return ((nv-1)%Mod);
}
void MakeRec()
{
	int i,j;
	for(i=1;i<=n;i++)
	{
		Clear();
		for(j=1;j<=n;j++)
		{
			if(map[i][j])
				lu[i][j]=Add(up[i][j]);
			else
				Clear();
			slu[i][j]=(slu[i-1][j]+slu[i][j-1]-slu[i-1][j-1]+lu[i][j]+Mod)%Mod;
		}
	}
	for(i=n;i>=1;i--)
	{
		Clear();
		for(j=1;j<=n;j++)
		{
			if(map[i][j])
				ld[i][j]=Add(down[i][j]);
			else
				Clear();
			sld[i][j]=(sld[i+1][j]+sld[i][j-1]-sld[i+1][j-1]+ld[i][j]+Mod)%Mod;
		}
	}
	for(i=1;i<=n;i++)
	{
		Clear();
		for(j=n;j>=1;j--)
		{
			if(map[i][j])
				ru[i][j]=Add(up[i][j]);
			else
				Clear();
			sru[i][j]=(sru[i-1][j]+sru[i][j+1]-sru[i-1][j+1]+ru[i][j]+Mod)%Mod;
		}
	}
	for(i=n;i>=1;i--)
	{
		Clear();
		for(j=n;j>=1;j--)
		{
			if(map[i][j])
				rd[i][j]=Add(down[i][j]);
			else
				Clear();
			srd[i][j]=(srd[i+1][j]+srd[i][j+1]-srd[i+1][j+1]+rd[i][j]+Mod)%Mod;
		}
	}
}
void GetAns()
{
	int i,j;
	int ans=0;
	for(i=1;i<n;i++)
	{
		ans+=(slu[i][n]-slu[i-1][n])*sld[i+1][n];
		ans+=(slu[n][i]-slu[n][i-1])*sru[n][i+1];
		ans%=Mod;
		if(ans<0)
			ans+=Mod;
	}
	for(i=1;i<n;i++)
	{
		for(j=1;j<n;j++)
		{
			ans-=lu[i][j]*srd[i+1][j+1];
			ans%=Mod;
			if(ans<0)
				ans+=Mod;
		}
	}
	for(i=1;i<n;i++)
	{
		for(j=2;j<=n;j++)
		{
			ans-=ru[i][j]*sld[i+1][j-1];
			ans%=Mod;
			if(ans<0)
				ans+=Mod;
		}
	}
	cout<<ans<<endl;
}
int main()
{
	freopen("rect.in","r",stdin);
	freopen("rect.out","w",stdout);
	GetData();
	MakeLine();
	MakeRec();
	GetAns();
	return 0;
}