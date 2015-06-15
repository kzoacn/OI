#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1e6+6;
const int mo=100000007;
int n,m;
LL f[maxn],g[maxn],fac[maxn];
LL pw(LL x,LL k,LL p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;
	}return ans;
}
int main(){
	cin>>n>>m;g[0]=1;
	LL two=pw(2,n,mo)-1;
	for(int i=1;i<=m;i++)
		g[i]=g[i-1]*(two-i+1)%mo;
	f[1]=f[2]=0;
	for(int i=3;i<=m;i++){
		f[i]=g[i-1];
		f[i]=(f[i]-f[i-1]+mo)%mo;
		f[i]=(f[i]-f[i-2]*(i-1)%mo*(two-i+2)%mo+mo)%mo;
	}LL tmp=1;for(int i=1;i<=m;i++)tmp=tmp*i%mo;
	cout<<f[m]*pw(tmp,mo-2,mo)%mo<<endl;   
	return 0;
}

