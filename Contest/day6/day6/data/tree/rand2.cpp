#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100000
using namespace std;
int data()
{
	return rand()<<15|rand();
}
int randint(int l,int r)
{
	return data()%(r-l+1)+l;
}
int n,Q,rank[maxn],L;
int main()
{
	srand(time(0));
	freopen("tree10.in","w",stdout);
	n=50000,Q=50000,L=randint(n-50,n-10);
	for(int i=1;i<=n;++i)
		rank[i]=i;
	random_shuffle(rank+1,rank+n+1);
	printf("%d\n",n);
	for(int i=2;i<=L;++i)
		printf("%d %d\n",rank[i],rank[i-1]);
	for(int i=L+1;i<=n;++i)
		printf("%d %d\n",rank[i],rank[randint(1,i-1)]);
	printf("%d\n",Q);
	for(int i=1;i<=Q;++i)
	{
		int t=randint(1,5);
		if(t==1)
			printf("CVal %d %d %d\n",randint(1,n),randint(0,1),randint(1,1000));
		else if(t==2)
			printf("CColor %d %d %d\n",randint(1,n),randint(0,1),randint(0,1));
		else if(t==3)
			printf("QMax %d %d\n",randint(1,n),randint(1,n));
		else if(t==4)
			printf("Cover %d %d %d\n",randint(1,n),randint(1,n),randint(0,1));
		else
			printf("QLen %d %d\n",randint(1,n),randint(1,n));
	}
	return 0;
}
