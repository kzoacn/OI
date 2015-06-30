#include<bits/stdc++.h>
using namespace std;
const int maxn=30010;
int n,d;
int ans=0;
int a[maxn],mx;
int dp[maxn][505];
bool vis[maxn][505];
int max3(int x,int y,int z){return max(max(x,y),z);}
int solve(int x,int tmpl){
	if(x>mx)return 0;
	int l=tmpl-(d-250);
	if(vis[x][l])return dp[x][l];
	vis[x][l]=1;
	int ans=0;
	if(tmpl==1){
		ans=a[x]+max(solve(x+tmpl,tmpl),solve(x+tmpl+1,tmpl+1));
	}else{
		ans=a[x]+max3(solve(x+tmpl-1,tmpl-1),solve(x+tmpl,tmpl),solve(x+tmpl+1,tmpl+1));
	}
	return dp[x][l]=ans;
}
int main(){
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		a[x]++;mx=max(mx,x);
	}
	cout<<solve(d,d)<<endl;
	return 0;
}
