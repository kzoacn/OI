#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
vector<int>G[maxn];
int n;
int ans=0,dep[maxn],a[maxn],b[maxn],fa[maxn];
vector<int>anss;
void dfs(int u,int r0,int r1){
	if(dep[u]%2==0){
		if((a[u]^r0)!=b[u])
			r0^=1,anss.push_back(u);
	}else{
		if((a[u]^r1)!=b[u])
			r1^=1,anss.push_back(u);
	}	
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(fa[u]==v)continue;
		fa[v]=u;dep[v]=dep[u]+1;
		dfs(v,r0,r1);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	dfs(1,0,0);
	cout<<anss.size()<<endl;
	for(int i=0;i<anss.size();i++)
		cout<<anss[i]<<endl;
	return 0;
}
