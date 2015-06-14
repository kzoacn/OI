#include<bits/stdc++.h>
using namespace std;
const int maxn=80;
int n;
int T=0;
char s[80][80];
int w[80][80];
int vis[80],Link[80];
int find(int x){
	for(int i=1;i<=n;i++)if(w[x][i]){
		int v=i;
		if(vis[v])continue;
		vis[v]=1;
		if(!Link[v]||find(Link[v])){
			Link[v]=x;return 1;
		}
	}return 0;
}
int main(){
	while(scanf("%d",&n)!=EOF){
		for(int i=1;i<=n;i++)
			scanf("%s",s[i]+1);
		memset(w,0,sizeof w);
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		if(s[i][j]=='1')w[i][j]=1;
		
		int ans=0;
		memset(Link,0,sizeof Link);
		for(int i=1;i<=n;i++){
			memset(vis,0,sizeof vis);
			if(find(i))ans++;
		}printf("Case %d: %d\n",++T,n-ans);
	}
	return 0;
}
