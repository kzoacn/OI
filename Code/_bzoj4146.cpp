#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+6;
typedef long long LL;
int n,mx;
int p[maxn],minp[maxn],a[maxn];
LL d[maxn];
int main(){
	freopen("bzoj4146.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		a[i]=x;
	}int ans=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)if(i!=j)
	ans+=a[i]%a[j]==0;
	cout<<ans<<endl;
	return 0;
}
