#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD=999911659;
LL pw(LL x,LL k,LL p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;
	}return ans;
}
LL inv(LL x){return pw(x,MOD-2,MOD);}
LL n,P;
LL ans=0;
int main(){
	cin>>n>>P;
	ans=((pw(10,n%(MOD-1),MOD)+MOD-1)%MOD-(pw(10,n,P)-1+P)%P+MOD)%MOD*inv(P)%MOD;
	P*=10;
	ans-=((pw(10,n%(MOD-1),MOD)+MOD-1)%MOD-(pw(10,n,P)-1+P)%P+MOD)%MOD*inv(P)%MOD;
	ans=(ans+MOD)%MOD;
	P/=10;
	
	P*=9;
	ans-=((pw(10,n%(MOD-1),MOD)+MOD-1)%MOD-(pw(10,n,P)-1+P)%P+MOD)%MOD*inv(P)%MOD;
	ans=(ans+MOD)%MOD;
	P*=10;
	ans+=((pw(10,n%(MOD-1),MOD)+MOD-1)%MOD-(pw(10,n,P)-1+P)%P+MOD)%MOD*inv(P)%MOD;
	ans=(ans+MOD)%MOD;
	
	cout<<ans<<endl;
	
	return 0;
}
