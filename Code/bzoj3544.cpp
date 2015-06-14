#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=2e5+5;
int n;
LL a[maxn],m;
set<LL>S;
int main(){
	scanf("%d%lld",&n,&m);
	for(int i=1;i<=n;i++){
		LL x;scanf("%lld",&x);
		a[i]=(a[i-1]%m+x%m+m)%m;
	}LL ans=0;
	for(int i=1;i<=n;i++){
		set<LL>::iterator it;
		ans=max(ans,a[i]);
		if((it=S.upper_bound(a[i]))!=S.end())
			ans=max(ans,(a[i]-*it+m)%m);
		S.insert(a[i]);
	}cout<<ans<<endl;
	return 0;
}
