#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int maxn=105;
const int Mod=10007;
const int inf=1<<27;
char st[maxn][maxn];
int g[maxn][maxn];
int sum[maxn][maxn];
int zs[maxn][maxn],zx[maxn][maxn],ys[maxn][maxn],yx[maxn][maxn];
int ans=0,n;
/*struct node
{
	int a[maxn][maxn];
};
bool operator<(const node p,const node q)
{
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++){
			if (p.a[i][j]<q.a[i][j]) return true;
			if (p.a[i][j]>q.a[i][j]) return false;}
	return false;
}
map<node,int>q;*/
inline bool full(int i,int j,int l,int p)
{
int tot=(l-i+1)*(p-j+1);
	if (tot>=2&&(sum[l][p]-sum[l][j-1]-sum[i-1][p]+sum[i-1][j-1])==tot) return true;
	return false;
}
int ksm(int x,int y)
{
	int r=1;
	for (;y;y>>=1)
	{
		if (y&1) r=r*x%Mod;
		x=x*x%Mod;	
	}
	return r;
}
int inv(int x)
{
	return ksm(x,Mod-2);
}
int main()
{
	int ans=0;int i,j,l,p;
	freopen("rect.in","r",stdin);
	freopen("rect.out","w",stdout);
	scanf("%d",&n);
	for (i=1;i<=n;i++)
	{
		scanf("%s",st[i]+1);
		for (j=1;j<=n;j++)
		{
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+(st[i][j]=='C');
			g[i][j]=(st[i][j]=='C');
		}
	}	
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
		{
			zs[i][j]=zs[i-1][j]+zs[i][j-1]-zs[i-1][j-1];
			for (l=1;l<=i;l++)
				for (p=1;p<=j;p++)
					if (full(l,p,i,j)) zs[i][j]++;
			zs[i][j]=(zs[i][j]+Mod)%Mod;
		}	
	for (i=1;i<=n;i++)
		for (j=n;j>=1;j--)
		{
			ys[i][j]=ys[i-1][j]+ys[i][j+1]-ys[i-1][j+1];
			for (l=1;l<=i;l++)
				for (p=j;p<=n;p++)
					if (full(l,j,i,p)) ys[i][j]++;
			ys[i][j]=(ys[i][j]+Mod)%Mod;
		}
	for (i=n;i>=1;i--)
		for (j=1;j<=n;j++)
		{
			zx[i][j]=zx[i+1][j]+zx[i][j-1]-zx[i+1][j-1];
			for (l=i;l<=n;l++)
				for (p=1;p<=j;p++)
					if (full(i,p,l,j)) zx[i][j]++;
			zx[i][j]=(zx[i][j]+Mod)%Mod;
		}
	for (i=n;i>=1;i--)
		for (j=n;j>=1;j--)
		{
			yx[i][j]=yx[i+1][j]+yx[i][j+1]-yx[i+1][j+1];
			for (l=i;l<=n;l++)
				for (p=j;p<=n;p++)
					if (full(i,j,l,p)) yx[i][j]++;
			yx[i][j]=(yx[i][j]+Mod)%Mod;
		}
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
		if (g[i][j]==1)
		{
			for (l=i;l<=n;l++)
				for (p=j;p<=n;p++)
				{
					int tot=(l-i+1)*(p-j+1);
					if (tot>=2&&(sum[l][p]-sum[l][j-1]-sum[i-1][p]+sum[i-1][j-1])==tot)
					{
						ans+=zs[n][j-1]+zs[i-1][n]+zx[l+1][n]+ys[n][p+1]-zs[i-1][j-1]-ys[i-1][p+1]-zx[l+1][j-1]-yx[l+1][p+1];
					}
					if (ans<0) ans=ans+((-ans)/Mod+1)*Mod;
					if (ans>inf) ans%=Mod;
				}
			}
	printf("%d\n",ans%Mod*inv(2)%Mod);
}
