#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mo=10000007;
LL N;
LL C[60][60];
LL f[60];
LL pw(LL x,LL k,LL p=mo){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;
	}return ans;
}
int main(){
	cin>>N;
	for(int i=0;i<60;i++){
		C[i][0]=1;	
		for(int j=1;j<=i;j++)
		C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	LL ans=1,k=0;
	for(int i=60;i>=0;i--)if(N>>i&1){
		ans=ans*(k+1)%mo;
		for(int j=1;j<=i;j++)
			ans=ans*pw(k+j,C[i][j])%mo;
		k++;
	}cout<<ans<<endl;
	return 0;
}
