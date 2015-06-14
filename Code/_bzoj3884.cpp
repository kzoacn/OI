#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL pw(int x,int k,int p){
	k%=p;while(k<0)k+=p;
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=(LL)ans*x%p;
		x=(LL)x*x%p;
	}return ans;
}
int T,x;
int solve(int p){
	int ans=2;
	for(int i=1;i<=1e5;i++)
	ans=pw(2,ans,p);
	return ans;
}
int main(){
	cin>>T;
	while(T--)cin>>x,cout<<solve(x)<<endl;
}
