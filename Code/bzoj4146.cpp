#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+6;
typedef long long LL;
int n,mx;
int p[maxn],minp[maxn],a[maxn];
int d[maxn];
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
int main(){
	freopen("bzoj4146.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x=in();
		a[x]++;mx=max(x,mx);
	}
	for(int i=1;i<=mx;i++)
	for(int j=i;j<=mx;j+=i)
		d[j]+=a[i];
	LL ans=0;
	for(int i=1;i<=mx;i++)
		ans+=(LL)a[i]*d[i];
	ans-=n;
	cout<<ans<<endl;
	return 0;
}
