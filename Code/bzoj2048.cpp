#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int n,m,R,S;
LL sum[20][20],lim;
int a[20][20],last[20];
bool ok(){
	for(int i=1;i<=R;i++){
	
	}
	return 1;
}
bool dfs(int x){
	if(x>R||last[x-1]==n){
		return ok();
	}
	for(int i=last[x-1]+1;i<=n;i++){
		last[x]=i;
		if(dfs(x+1))
			return 1;
		last[x]=0;
	}return 0;
}
int main(){
	cin>>n>>m>>R>>S;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
	cin>>a[i][j],sum[i][j]=sum[i-1][j]+sum[i][j-1]+a[i][j];
	int l=0,r=sum[n][m]+1;
	while(l<r){
		int mid=(l+r)>>1;lim=mid;
		memset(last,0,sizeof last);
		if(dfs(1))
			r=mid;
		else l=mid+1;
	}cout<<l<<endl;
	return 0;
}
