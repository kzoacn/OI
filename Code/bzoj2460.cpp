#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int n,ans;
pair<int,LL>a[1001];
LL base[64];
bool add(LL x){
	for(LL i=63;i>=0;i--){
		if(x>>i&1){
			if(!base[i]){base[i]=x;return true;}
			else x^=base[i];
		}
	}return false;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].second>>a[i].first;
	sort(a+1,a+1+n,greater<pair<int,LL> >());
	for(int i=1;i<=n;i++)
		if(add(a[i].second))ans+=a[i].first;
	cout<<ans<<endl;
	return 0;
}
