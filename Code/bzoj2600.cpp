#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1e5+5;
int n;
LL L,B;
int a[maxn];
LL sum[maxn];
#define sum(l,r) (sum[r]-sum[l-1])
LL cost(int l,int r){
	int mid=(l+r)>>1;
	LL ans=0;
	ans+=(LL)a[mid]*(mid-l+1)-(LL)a[mid]*(r-mid);
	ans-=sum(l,mid);
	ans+=sum(mid+1,r);
	return ans;
}
int main(){
	cin>>n>>L>>B;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}int ans=0;
	for(int i=1,j=1;j<=n;j++){
		while(cost(i,j)>B)i++;
		ans=max(ans,j-i+1);
	}cout<<ans<<endl;
	return 0;
}
