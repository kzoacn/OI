#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m;scanf("%d%d",&n,&m);
	static int a[50010];
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	static int cnt[50010];
	while(m--){
		int l,r;scanf("%d%d",&l,&r);
		memset(cnt,0,sizeof cnt);
		int ans=0;
		for(int i=l;i<=r;i++)cnt[a[i]]++;
		for(int i=1;i<=n;i++)ans+=cnt[i]*cnt[i];
		cout<<ans<<endl;
	}
	return 0;
}
