#include<bits/stdc++.h>
using namespace std;
const int maxn=1e7+5;
typedef long long LL;
LL T,x;
int phi[maxn];
int p[664580],two[maxn];
bool notp[maxn];
LL pw(LL x,LL k,LL p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=(LL)ans*x%p;
		x=(LL)x*x%p;
	}return ans;
}
LL compute(LL x){
	if(x<=2)return 0;
	if(x==(1<<two[x]))return 0;
	return pw(2,compute(phi[x])+phi[x],x); 
}
int main(){
	phi[1]=1;
	for(LL i=2;i<maxn;i++){
		for(LL j=i;!(j&1);j>>=1)two[i]++;
		if(!notp[i])p[++p[0]]=i,phi[i]=i-1;
		for(LL j=1;j<=p[0]&&i*p[j]<maxn;j++){
			notp[i*p[j]]=1;
			if(i%p[j]==0){
				phi[i*p[j]]=phi[i]*p[j];
				break;
			}else phi[i*p[j]]=phi[i]*(p[j]-1);
		}
	}cin>>T;
	while(T--){
		cin>>x;
		cout<<compute(x)<<endl;
	}
	return 0;
}
