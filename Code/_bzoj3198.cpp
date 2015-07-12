#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<functional>
#include<cmath>
#include<cctype>
#include<map>
using namespace std;
#define For(i,n) for(int i=1;i<=n;i++)
#define Rep(i,n) for(int i=0;i<n;i++)
#define Fork(i,k,n) for(int i=k;i<=n;i++)
#define ForD(i,n) for(int i=n;i;i--)
#define ForkD(i,k,n) for(int i=n;i>=k;i--)
#define Forp(x) for(int p=pre[x];p;p=next[p])
#define RepD(i,n) for(int i=n;i>=0;i--)
#define MEM(a) memset(a,0,sizeof(a))
#define MEMI(a) memset(a,127,sizeof(a))
#define MEMi(a) memset(a,128,sizeof(a))
#define INF (2139062143)
#define F (300007)
#define MAXN (100000+10)
#define BASE (13131)
#define MAXK (6+1)
int n,k; 
long long a[MAXN][7];
int bin[7]={0,1,2,4,8,16,32};
long long h[F+10],hnum[F+10][7];
int st[MAXN],size=0;
bool equal(long long h1[7],long long h2[7],int p)
{
	For(j,6) if (p&bin[j]) if (h1[j]^h2[j]) return 0;
	return 1; 
}
int hash(int i,int p)
{
	long long ans=0;
	For(j,6) if (p&bin[j]) ans=(ans*BASE+a[i][j])%F;
	while (h[ans]>0&&(!equal(hnum[ans],a[i],p))) ans=(ans+1)%F;
	memcpy(hnum[ans],a[i],sizeof(hnum[ans])); 
	return ans;
}
long long ans[MAXN]={0};
int bitcount(int p)
{
	int i=0;
	For(j,6) if (bin[j]&p) i++;
	return i;
}
long long calc(int p)
{
	long long ans=0;
	size=0;
	For(i,n)
	{
		int t=hash(i,p);
		h[t]++;st[++size]=t;
	}
	For(i,size)
		if (h[st[i]])
		{
			ans+=h[st[i]]*(h[st[i]]-1)/2;						
			h[st[i]]=0;memset(hnum[st[i]],0,sizeof(hnum[st[i]]) );
		} 
	return ans;
}
long long C[MAXK*2][MAXK*2]={0};
int main()
{
//	freopen("bzoj3197.in","r",stdin);
//	freopen("bzoj3197.out","w",stdout);
	scanf("%d%d",&n,&k);
	For(i,n) For(j,6) scanf("%lld",&a[i][j]);
	For(i,64/*(1<<6)-1*/)
	{
		long long delta=calc(i);
		if (delta) ans[bitcount(i)]+=delta;//,cout<<i<<' ';
	}
	C[0][0]=1;
	For(i,12)
	{
		C[i][0]=1;C[i][1]=i;
		Fork(j,2,12) C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	//cout<<C[2][0]<<' '<<C[2][1]<<' '<<C[2][2]<<endl;
//	Rep(i,7) cout<<ans[i]<<endl;
	
	ForkD(i,k,6) 
	{
		Fork(j,i+1,6) ans[i]-=C[j][j-i]*ans[j];
	}
//	Rep(i,7) cout<<ans[i]<<endl;
	
	cout<<ans[k]<<endl;
	
	return 0;
}
