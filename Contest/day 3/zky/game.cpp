#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m;
int vis[1<<20],f[1<<20];
int dfs(int S){
	if(S>>(n-1)&1)return 0;
	if(vis[S])return f[S];
	int ans=0;vis[S]=1;
	for(int i=0;i<n;i++)if(S>>i&1){
		for(int j=i+1;j<n;j++)if(!(S>>j&1)){
			if(!dfs(S^(1<<i)^(1<<j)))
				ans++;
			break;
		}
	}return f[S]=ans;
}
int main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d%d",&n,&m);
	int S=0;
	for(int i=1;i<=m;i++){
		int x;scanf("%d",&x);
		S|=1<<(x-1); 
	}
	cout<<dfs(S)<<endl;
	return 0;
}
