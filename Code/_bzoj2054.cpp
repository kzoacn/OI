#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#define M 10000000+5
using namespace std;
int f[M],n,m,p,q,c[M];
int Getfather(int x)
{
	if (f[x]==x||!f[x])
		return f[x]=x;
	return f[x]=Getfather(f[x]);
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&p,&q);
	int tot=0;
        for (int i=m;i;i--)
	{
		int l=((long long)i*p+q)%n+1,r=((long long)i*q+p)%n+1;
		if (l>r) swap(l,r);
		for (int k=Getfather(l);k<=r;k=Getfather(k))
		{
			c[k]=i;
			tot++;
			f[k]=k+1;
		}
		if (tot==n) break;
	}
	for (int i=1;i<=n;i++)
		printf("%d\n",c[i]);
	return 0;
}

