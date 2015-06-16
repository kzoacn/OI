#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL pow(LL x,LL k,LL mo){
	LL an=1;
	for(;k;k>>=1){
		if(k&1)an=an*x%mo;
		x=x*x%mo;
	}return an;
}
LL n;
int main(){
	cin>>n;
	LL ans=1;
	for(LL i=1;i<n;i++)ans=ans*i%9999991;
	cout<<ans*pow(n,n-2,9999991)%9999991<<endl;
	return 0;
}
