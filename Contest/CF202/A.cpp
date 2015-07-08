#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n;
int a[maxn],b[maxn];
bool check(int mid){
	for(int i=1;i<=n;i++)b[i]=a[i]-mid;
	for(int i=n;i>=1;i--){
		mid+=b[i];
		if(mid<=0)return 1;
	}
	return mid<=0;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	int l=a[n],r=a[n]*2+233;
	while(l<r){
		int mid=((long long)l+r)/2;
		if(check(mid))
			r=mid;
		else l=mid+1;
	}cout<<r<<endl;
	return 0;
}
