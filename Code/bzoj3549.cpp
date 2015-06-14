#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n;
int a[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i]+=a[i-1];
	int ans=0;
	for(int i=1;i<=n;){
		int j=lower_bound(a+i,a+1+n,(a[n]-a[i])/2.0+a[i-1]-1e-9)-a;
		i=j+1;ans++;
	}cout<<ans<<endl;
	return 0;
}
