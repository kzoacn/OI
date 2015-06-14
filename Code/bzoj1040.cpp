#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
typedef long long LL;
vector<int>G[maxn];
int n;
int w[maxn],ins[maxn],vis[maxn];
LL f[maxn][2];
int x,y,fa[maxn];
int find(int x){return fa[x]==x?x:find(fa[x]);}
LL dp(int u,int t){
	if(f[u][t])return f[u][t];
	LL ans=t*w[u];
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==fa[u])continue;
		fa[v]=u;
		if(t)ans+=dp(v,0);
		else ans+=max(dp(v,0),dp(v,1));
	}return f[u][t]=ans;
}
vector<int>X,Y;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++){
		int v;
		scanf("%d%d",&w[i],&v);
		if(find(i)!=find(v)){
			G[i].push_back(v);
			G[v].push_back(i);
			fa[find(i)]=find(v);
		}else X.push_back(i),Y.push_back(v);
	}
	LL ans=0;
	for(int i=0;i<X.size();i++){
		fa[X[i]]=0;
		LL res=dp(X[i],0);
		memset(f,0,sizeof f);
		fa[Y[i]]=0;
		res=max(res,dp(Y[i],0));
		ans+=res;
		//cout<<ans<<endl;
	}cout<<ans<<endl;
	return 0;
}
