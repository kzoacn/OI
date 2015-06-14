#include<bits/stdc++.h>
using namespace std;
const int maxn=5005;
typedef long long LL;
int n;
vector<int>G[maxn];
LL C(LL n,LL m){
	if(n<m)return 0;
	return n*(n-1)*(n-2)/6;
}
LL dep[maxn];
LL one[maxn];
LL two[maxn];
void dfs(int u,int fa,int d){
	dep[d]++;
	for(int v,i=0;i<G[u].size();i++)if((v=G[u][i])!=fa)dfs(v,u,d+1);
}
LL calc(int s){
	LL ans=0;
	memset(one,0,sizeof one);
	memset(two,0,sizeof two);
	for(int i=0;i<G[s].size();i++){
		int v=G[s][i];
		memset(dep,0,sizeof dep);
		dfs(v,s,1);
		for(int i=1;i<=n;i++){
			ans+=dep[i]*two[i];
			two[i]+=one[i]*dep[i];
			one[i]+=dep[i];
		}
	}return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}long long ans=0;
	for(int i=1;i<=n;i++)
	ans+=calc(i);
	cout<<ans<<endl;
	return 0;
}
