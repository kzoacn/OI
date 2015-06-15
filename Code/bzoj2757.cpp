#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mo=20120427;
namespace zero{
	 LL cal(LL x){
	 
	 }
}
const int M=1e6+3;
struct hashtab{
	LL a[M],s[M];
	int b[M],sz;
	int& operator[](LL x){
		x%=M;int _x=x%M;
		while(a[_x]&&a[_x]!=x)_x++;
		if(!a[_x])a[_x]=x,s[sz++]=x;
		return b[_x];
	}
}f[19],g[19];
LL cal(LL x,LL k){
	
}
int main(){
	int T;scanf("%d",&T);f[0][1]=1;
	for(int i=0;i<19;i++)for(int j=0;j<f[i].sz;j++)for(int k=1;k<=9;k++){
		LL v=f[i].s[j];
		if(v*k>LL(1e18))break;
		(f[i+1][v*k]+=f[i][v])%=mo;
		(g[i+1][v*k]+=g[i][v]*10%mo+f[i][v]*k%mo)%=mo;		
	}
	while(T--){
		LL l,r,k;scanf("%lld%lld%lld",&l,&r,&k);
		if(k==0)printf("%lld\n",zero::cal(r)-zero::cal(l-1));
		else printf("%lld\n",cal(r,k)-cal(l-1,k));
	}
	return 0;
}
