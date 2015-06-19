#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
typedef long long LL;
LL n=2,m=10;
LL a[233][233];
LL rnd(){
	return (rand()<<16)|rand();
}
LL ran(){
	return (rnd()<<32)|rnd();
}
LL range(LL l,LL r){
	return ran()%(r-l)+l;
}

void sol(){
	m=range(LL(5),LL(10));
	printf("%lld %lld\n",n,m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
		a[i][j]=range(m,m+100);
//		if(rand()%2)a[i][j]=0;
	}
	a[1][1]=range(m,m+100);;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	printf("%lld%c",a[i][j]," \n"[j==n]);
}
int main(){
	srand(time(0)^getpid());
	int T=5;
	printf("%d\n",T);
	while(T--)sol();
	return 0;
}
