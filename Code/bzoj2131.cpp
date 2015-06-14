#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int n,m;
LL ans;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		LL x;cin>>x;ans+=x*(i*i+j*j);
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		LL x;cin>>x;ans-=x*(i*i+j*j);
	}
	cout<<ans/2<<endl;
	return 0;
}
