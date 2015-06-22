#include<bits/stdc++.h>
using namespace std;
const int maxn=3010;
vector<int>G[maxn];
int d[maxn][maxn],d2[maxn];
int s1,t1,s2,t2,l1,l2,n,m;
void bfs(int s,int d[]){
	static int vis[maxn];
	memset(vis,0,sizeof vis);
	queue<int>q;q.push(s);vis[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(vis[v])continue;
			vis[v]=1;q.push(v);d[v]=d[u]+1;
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);G[v].push_back(u);
	}
	scanf("%d%d%d",&s1,&t1,&l1);
	scanf("%d%d%d",&s2,&t2,&l2);
	for(int i=1;i<=n;i++)bfs(i,d[i]);
	if(d[s1][t1]>l1||d[s2][t2]>l2)return puts("-1"),0;
	int ans=d[s1][t1]+d[s2][t2];
	for(int x=1;x<=n;x++)
	for(int y=1;y<=n;y++){
		if(d[s1][x]+d[x][y]+d[y][t1]<=l1
			&&d[s2][x]+d[x][y]+d[y][t2]<=l2){
			ans=min(ans,d[s1][x]+d[x][y]+d[y][t1]+d[s2][x]+d[y][t2]);	
		}
		if(d[s1][x]+d[x][y]+d[y][t1]<=l1
			&&d[s2][y]+d[y][x]+d[x][t2]<=l2){
			ans=min(ans,d[s1][x]+d[x][y]+d[y][t1]+d[s2][y]+d[x][t2]);	
		}		
	}cout<<m-ans<<endl;
	return 0;
}
