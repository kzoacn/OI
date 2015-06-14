#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 16400
#define mo 1004535809
#define INF 0x3f3f3f3f
#define G 3
using namespace std;
int n,m,d,X,S;
int ind[M];
long long Quick_Power(long long x,int y,int p)
{
	long long re=1;
	while(y)
	{
		if(y&1) (re*=x)%=p;
		(x*=x)%=p; y>>=1;
	}
	return re;
}
void NTT(int a[],int n,int type)
{
	static int temp[M];
	int i;
	if(n==1) return ;
	for(i=0;i<n;i+=2)
		temp[i>>1]=a[i],temp[i+n>>1]=a[i+1];
	memcpy(a,temp,sizeof(a[0])*n);
	int *l=a,*r=a+(n>>1);
	NTT(l,n>>1,type);
	NTT(r,n>>1,type);
	long long w=Quick_Power(G,(long long)type*(mo-1)/n%(mo-1),mo),wn=1;
	for(i=0;i<n>>1;i++,(wn*=w)%=mo)
		temp[i]=(l[i]+wn*r[i])%mo,temp[i+(n>>1)]=(l[i]-wn*r[i]%mo+mo)%mo;
	memcpy(a,temp,sizeof(a[0])*n);
}
struct GF{
	int a[M];
	GF() {}
	GF(bool)
	{
		memset(a,0,sizeof a);
		a[0]=1;
	}
	int& operator [] (int x)
	{
		return a[x];
	}
	GF& operator *= (const GF &f)
	{
		static int b[M];
		int i;
		memcpy(b,f.a,sizeof b);
		NTT(a,d,1);
		NTT(b,d,1);
		for(i=0;i<d;i++)
			a[i]=(long long)a[i]*b[i]%mo;
		NTT(a,d,mo-2);
		for(i=m-1;i<=m-2<<1;i++)
			(a[i-(m-1)]+=a[i])%=mo,a[i]=0;
		long long inv=Quick_Power(d,mo-2,mo);
		for(i=0;i<=m-2;i++)
			a[i]=a[i]*inv%mo;
		return *this;
	}
}a;
int Get_Primitive_Root()
{
	static int stack[M],top;
	int i,j,temp=m-1;
	for(i=2;i<=temp;i++)
		if(temp%i==0)
		{
			stack[++top]=i;
			while(temp%i==0)
				temp/=i;
		}
	for(i=2;;i++)
	{
		for(j=1;j<=top;j++)
			if(Quick_Power(i,(m-1)/stack[j],m)==1)
				break;
		if(j==top+1)
			return i;
	}
}
GF Quick_Power(GF &x,int y)
{
	GF re(true);
	while(y)
	{
		if(y&1) re*=x;
		x*=x; y>>=1;
	}
	return re;
}
int main()
{
	int i,x;
	cin>>n>>m>>X>>S;
	for(d=1;d<=m+m;d<<=1);
	int g=Get_Primitive_Root();
	for(i=0,x=1;i<m-1;i++,(x*=g)%=m)
		ind[x]=i;
	for(i=1;i<=S;i++)
	{
		scanf("%d",&x);
		if(!x) continue;
		a[ind[x]]=1;
	}
	GF ans=Quick_Power(a,n);
	cout<<ans[ind[X]]<<endl;
	return 0;
}

