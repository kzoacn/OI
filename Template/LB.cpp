#include<bits/stdc++.h>
using namespace std;
int n;
int w[101],bs[32];
bool add(int x){
	for(int i=31;i>=0;i--){
		if(x>>i&1){
			if(!bs[i]){bs[i]=x;return 1;}
			else x^=bs[i];
		}
	}return 0;
}
int main(){
	cin>>n;long long ans=0;
	for(int i=1;i<=n;i++)cin>>w[i];
	sort(w+1,w+1+n,greater<int>());
	for(int i=1;i<=n;i++)if(add(w[i]))ans+=w[i];
	cout<<accumulate(w+1,w+1+n,0LL)-ans<<endl;
	return 0;
}
