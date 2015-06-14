#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
vector<int>G[maxn];
int rt,fa[maxn],n,m;
int anss[maxn],maxd[maxn],tmp[maxn];
void dfs(int u){
	for(int v,i=0;i<G[u].size();i++){
		if((v=G[u][i])!=fa[u]){
			fa[v]=u;
			dfs(v);
			maxd[u]=max(maxd[u],maxd[v]+1);
			anss[u]=max(anss[u],anss[v]);
		}
	}vector<int>vec;anss[u]=max(anss[u],maxd[u]);
	for(int v,i=0;i<G[u].size();i++)if((v=G[u][i]!=fa[u]))vec.push_back(maxd[G[u][i]]+1);
	if(vec.size()<=1)return;
	sort(vec.begin(),vec.end());
	anss[u]=max(anss[u],vec.back()+vec[vec.size()-2]);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}scanf("%d",&rt);dfs(rt);
	scanf("%d",&m);
	while(m--){
		int u;scanf("%d",&u);
		printf("%d\n",anss[u]);
	}
	return 0;
}
