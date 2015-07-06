#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL a,b,ans;
LL solve(LL a,LL b){
	LL ans=0;
	if(a>=b)ans=a/b,a%=b;
	if(!a)return ans;
	return ans+1+solve(a,b-a);
}
LL gcd(LL a,LL b){
	if(!b)return 0;
	return gcd(b,a%b)+a/b;
}
int main(){

	cin>>a>>b;
	cout<<gcd(a,b)<<endl;
//	cerr<<solve(a,b)<<endl;
	
	return 0;
}


