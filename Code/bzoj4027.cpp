#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+1;
typedef long long LL;
int n,m;
vector<int>G[maxn];
int ans=0;
LL cost[maxn];
bool bycost(int x,int y){
	return cost[x]<cost[y];
}
void dfs(int u){
	for(int i=0;i<G[u].size();i++)dfs(G[u][i]);
	sort(G[u].begin(),G[u].end(),bycost);
	cost[u]+=G[u].size();
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(cost[u]+cost[v]-1<=m){
			ans++;
			cost[u]+=cost[v]-1;
		}else break;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)scanf("%d",&cost[i]);
	for(int i=0;i<n;i++){
		int x;scanf("%d",&x);
		while(x--){
			int v;scanf("%d",&v);
			G[i].push_back(v);
		}
	}dfs(0);
	cout<<ans<<endl;
	return 0;
}
