#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL sol(LL n,LL A,LL B,LL C){
	LL ans=0;
	if(B>=C)ans+=n*(B/C),B%=C;
	if(A>=C)ans+=(A/C)*(n*(n+1)/2),A%=C;
	ans+=sol((A*n+B)/C,C,(A*n+B)%C,A);
	return ans;
}
int main(){
	LL A,B,C;
	cin>>A>>B>>C;
	cout<<sol(C/A,-A,C,B)+C/B+A/B-1<<endl;
	return 0;
}
