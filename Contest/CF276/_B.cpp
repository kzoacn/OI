#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;;
int n;
int a[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	int ans=0;
	for(int i=1;i<=n;i++)
	for(int j=i;j<=n;j++)
	ans=max(ans,a[j]%a[i]);
	cout<<ans<<endl;
	return 0;
}
