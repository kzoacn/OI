#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
vector<int>G[maxn],E[maxn];
int n,m;
int vis[maxn];
vector<int>vec;
int C,col[maxn];
void dfs(int u){
	vis[u]=1;col[u]=C;vec.push_back(u);
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(!vis[v])dfs(v);
	}
}
int ins[maxn],vis2[maxn];
bool dfs2(int u){
	ins[u]=C;vis2[u]=C;
	for(int i=0;i<E[u].size();i++){
		int v=E[u][i];
		if(ins[v]==C)return true;
		if(vis2[v]!=C)if(dfs2(v))return true;
	}
	ins[u]=0;
	return false;
}
int main(){
	scanf("%d%d",&n,&m);
	while(m--){
		int u,v;scanf("%d%d",&u,&v);
		E[u].push_back(v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	int ans=n;
	for(int i=1;i<=n;i++)if(!vis[i]){
		vec.clear();
		C++;dfs(i);
		int flag=0;
		for(int i=0;i<vec.size();i++)
		if(dfs2(vec[i])){
			flag=1;break;
		}
		ans-=!flag;
	}
	cout<<ans<<endl;
	return 0;
}
