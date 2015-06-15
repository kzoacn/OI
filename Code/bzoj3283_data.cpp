#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int range(int l,int r){return rand()%(r-l)+l;}
typedef long long LL;
LL pow(LL x,LL k,LL p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;
	}return ans;
}
int main(){
	srand(time(0)^getpid());
	int T=50;
	printf("%d\n",T);
	while(T--){
		LL a=range(1,1000),x=range(0,1000),p=range(1,1000);
		printf("2 %lld %lld %lld\n",a,pow(a,x,p),p);
	}
	return 0;
}
