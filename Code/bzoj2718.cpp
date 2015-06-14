#include<bits/stdc++.h>
using namespace std;
int n,m,ans=0;
int vis[201],Link[201];
vector<int>G[201];
int mp[201][201];
int find(int x){
	for(int i=1;i<=n;i++){
		if(!mp[x][i]||vis[i])continue;
		vis[i]=1;
		if(!Link[i]||find(Link[i])){
			Link[i]=x;return 1;
		}
	}return 0;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		mp[u][v]=1;
	}for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	mp[i][j]|=mp[i][k]&mp[k][j];
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof vis);
		ans+=find(i);
	}cout<<n-ans<<endl;
	return 0;
}
