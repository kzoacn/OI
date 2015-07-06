#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int mo=1234567891;
typedef long long LL;
int T;
int k,a,n,d;
int pow(int x,int k,int mo){
	int ans=1;
	for(;k;k>>=1){
		if(k&1)ans=(LL)ans*x%mo;
		x=(LL)x*x%mo;
	}return ans;
}
LL f[int(1e6+2000)],g[int(1e6+2000)];
void sol(){
	cin>>k>>a>>n>>d;
	for(int i=1;i<=a+n*d;i++)f[i]=pow(i,k,mo);
	for(int i=1;i<=a+n*d;i++)f[i]=(f[i-1]+f[i])%mo;
	for(int i=1;i<=a+n*d;i++)g[i]=(g[i-1]+f[i])%mo;
	LL ans=0;
	for(int i=0;i<=n;i++)
		ans=(ans+g[a+i*d])%mo;
	cout<<ans<<endl;
}
int main(){
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	cin>>T;
	while(T--)sol();
	return 0;
}
