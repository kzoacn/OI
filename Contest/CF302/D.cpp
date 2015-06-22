#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
const int mo=1e9+7;
typedef long long LL;
int fa[maxn],n;
vector<int>G[maxn];
LL dw[maxn],up[maxn];
void dfs1(int u){
	dw[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		dfs1(v);
		dw[u]*=(dw[v]+1);
		dw[u]%=mo;
	}
}
void dfs2(int u){
	static LL pre[maxn],suf[maxn];
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		pre[i]=(i?pre[i-1]:1)*(dw[v]+1)%mo;
	}
	for(int i=int(G[u].size())-1;i>=0;i--){
		int v=G[u][i];
		suf[i]=(i+1<G[u].size()?suf[i+1]:1)*(dw[v]+1)%mo;
	}
	
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		//up[v]=(up[u]*dw[u]/(dw[v]+1)+1)
		up[v]=(up[u]*(i?pre[i-1]:1)%mo*(i+1<G[u].size()?suf[i+1]:1)%mo+1)%mo;
		
	}
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		//up[v]=(up[u]*dw[u]/(dw[v]+1)+1)
		dfs2(v);		
	}	
}
LL anss[maxn];
int main(){
	scanf("%d",&n);
	for(int i=2;i<=n;i++){
		scanf("%d",&fa[i]);
		G[fa[i]].push_back(i);
	}dfs1(1);
	up[1]=1;
	dfs2(1);
	for(int i=1;i<=n;i++)anss[i]=up[i]*dw[i]%mo;
	for(int i=1;i<=n;i++)
		printf("%I64d%c",anss[i]%mo," \n"[i==n]);
	return 0;
}
