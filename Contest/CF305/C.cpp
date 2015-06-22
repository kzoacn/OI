#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+5;
vector<int>d[maxn];
int a[maxn],n,m;
int mu[maxn],cnt[maxn],vis[maxn];
long long ans=0;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),vis[a[i]]=1;
	mu[1]=1;
	for(int i=1;i<maxn;i++)
	for(int j=i;j<maxn;j+=i){
		if(vis[j])d[j].push_back(i);
		if(i!=j)mu[j]-=mu[i];
	}memset(vis,0,sizeof vis);
	while(m--){
		int x;scanf("%d",&x);
		if(!vis[x]){
			for(int i=0;i<d[a[x]].size();i++)
				ans+=(long long)mu[d[a[x]][i]]*(cnt[d[a[x]][i]]++);
		}else{
			for(int i=0;i<d[a[x]].size();i++)
				ans-=(long long)mu[d[a[x]][i]]*(--cnt[d[a[x]][i]]);			
		}vis[x]^=1;
		printf("%lld\n",ans);
	}
	return 0;
}
