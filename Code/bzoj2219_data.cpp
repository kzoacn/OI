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
	int T=1000;
	printf("%d\n",T);
	while(T--){
		int x=range(1,1e9);
		int A=range(1,1e9);
		int K=range(1,5e8);
		int B=pow(x,A,2*K+1);	
		printf("%d %d %d\n",A,B,K);
	}
	return 0;
}
