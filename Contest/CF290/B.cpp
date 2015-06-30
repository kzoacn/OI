#include<bits/stdc++.h>
using namespace std;
const int maxn=305;
int n;
int l[maxn],c[maxn];
map<int,int>dp[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&l[i]);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	dp[1][0]=0;
	dp[1][l[1]]=c[1];
	for(int i=1;i<n;i++){
		dp[i+1]=dp[i];
		for(map<int,int>::iterator it=dp[i].begin();it!=dp[i].end();it++){
			int x=it->first,co=it->second;
			//dp[i][x]=co
			//dp[i+1][gcd(x,l[i+1])]=co+c[i+1]
			if(dp[i+1].count(__gcd(x,l[i+1])))
				dp[i+1][__gcd(x,l[i+1])]=min(dp[i+1][__gcd(x,l[i+1])],co+c[i+1]);
			else dp[i+1][__gcd(x,l[i+1])]=co+c[i+1];
		}
	}
	if(dp[n].count(1))cout<<dp[n][1]<<endl;
	else puts("-1");
	return 0;
}
