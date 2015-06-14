#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll; 
int n,k,m,i,ans,mod=1000000007,jc[2000010];
int pow(int a,int b,int mod){
	int c=1;
	for(;b;b>>=1)
	{
		if(b&1) c=(ll)c*a%mod;
		a=(ll)a*a%mod;
	}
	return c;
} 
ll C(int n,int m){
	ll a=jc[n],b=(ll)jc[m]*jc[n-m]%mod;
	return a*pow((int)b,mod-2,mod)%mod;
}
int main(){
	cin>>n>>k;
	if(n==k) {puts("1"); return 0;} 
	for(jc[0]=i=1;i<=n;i++) jc[i]=(ll)jc[i-1]*i%mod; 
	for(i=0,m=n-k;i<=m;i++)
		ans=(ans+C(m,i)*pow(2,pow(2,m-i,mod-1),mod)*(i&1?-1:1))%mod;
	cout<<(ans*C(n,k)%mod+mod)%mod<<endl;
	return 0;
}
