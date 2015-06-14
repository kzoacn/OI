#include<bits/stdc++.h>
using namespace std;
int dp[int(1e6)+6];
int main(){
	int n,l;scanf("%d%d",&n,&l);
	for(int i=1;i<=n;i++){
		int x,y=0;scanf("%d",&x);
		for(int j=1;j*j<=x;j++){
			if(x%j==0){
				y=max(y,dp[j]);
				y=max(y,dp[x/j]);
			}
		}y++;
		for(int j=1;j*j<=x;j++){
			if(x%j==0){
				if(j>=l)dp[j]=max(dp[j],y);
				if(x/j>=l)dp[x/j]=max(dp[x/j],y);
			}
		}
	}cout<<*max_element(dp+1,dp+1+int(1e6))<<endl;
	return 0;
}
