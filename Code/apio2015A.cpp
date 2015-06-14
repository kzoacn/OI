#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL ten[20];
LL A,B,K1,K2;
LL mul(LL x,LL y,LL p){
	LL ans=0;
	for(;y;y>>=1){
		if(y&1)ans=(ans+x)%p;
		x=(x+x)%p;
	}return ans;
}
LL pow(LL x,LL k,LL p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=mul(ans,x,p);
		x=mul(x,x,p);
	}return ans;
}
LL cur;
int calc(LL A,LL B,LL K){
	cur=cur*10%(10*B);
	return cur*A%(10*B)/B%10;
}
int main(){
	ten[0]=1;
	for(int i=1;i<18;i++)ten[i]=ten[i-1]*10;
	cin>>A>>B>>K1>>K2;A%=B;
	cur=pow(10,K1-1,10*B);
	for(LL i=K1;i<=K2;i++)
		printf("%d",calc(A,B,i));
	puts("");
	return 0;
}
