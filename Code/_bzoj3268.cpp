#include<bits/stdc++.h>
using namespace std;
int a[100];
int main(){
	int n;cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];a[i+n]=a[i];
	}int ans=0;
	for(int i=n+1;i<=2*n;i++){
		int res=0;
		int x=i;
		while(x>i-n)x-=a[x],res++;
		ans+=res;
	}cout<<ans<<endl;
	return 0;
}
