#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1e6+6;
int n,k;
const LL M=1000000007LL;
LL fac[maxn],inv[maxn],two[maxn];
LL C(LL n,LL m){return n-m<0?0:fac[n]*inv[m]%M*inv[n-m]%M;}
LL pw(LL x,LL k,LL p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;
	}return ans;
}
int main(){
	cin>>n>>k;
	fac[0]=inv[1]=inv[0]=two[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%M;
	for(int i=2;i<=n;i++)inv[i]=(M-M/i)*inv[M%i]%M;
	for(int i=1;i<=n;i++)inv[i]=inv[i]*inv[i-1]%M;
	LL ans=0;int cur=0;
	for(int i=k;i<=n;i++){
		cur^=1;
		LL res=C(n,i)*C(i,k)%M*(pw(2,pw(2,n-i,M-1),M)+M-1)%M;
		ans+=(cur?1:-1)*res;
		ans=(ans+M)%M;
	}cout<<(ans+M)%M<<endl;
	return 0;
}
