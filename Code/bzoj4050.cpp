#include<bits/stdc++.h>
using namespace std;
const int maxn=1001;
typedef long long LL;
int n;
struct C{
	int x,y,r;
}cir[maxn];
vector<int>G[maxn];
int fa[maxn],col[maxn],vis[maxn];
LL son[maxn],mom[maxn];
void make(LL &x,LL &y){
	LL t=__gcd(x,y);
	x/=t;y/=t;
}
void dfs(int u){
	vis[u]=1;
	make(son[u],mom[u]);
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];if(v==fa[u]||vis[v])continue;
		fa[v]=u;col[v]=col[u]^1;
		son[v]=son[u]*cir[u].r;
		mom[v]=mom[u]*cir[v].r;
		dfs(v);
	}
}
LL sqr(LL x){return x*x;}
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&cir[i].x,&cir[i].y,&cir[i].r);	
	for(int i=1;i<=n;i++)G[i].clear();
	for(int i=1;i<=n;i++)son[i]=mom[i]=2,col[i]=0;
	memset(vis,0,sizeof vis);
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)
	if(sqr(cir[i].x-cir[j].x)+sqr(cir[i].y-cir[j].y)==sqr(cir[i].r+cir[j].r))
		G[i].push_back(j),G[j].push_back(i);
	dfs(1);
	for(int i=1;i<=n;i++){
		if(son[i]==2&&mom[i]==2)puts("not moving");
		else{
			if(mom[i]==1)printf("%lld %s\n",son[i],col[i]?"counterclockwise":"clockwise");
			else printf("%lld/%lld %s\n",son[i],mom[i],col[i]?"counterclockwise":"clockwise");
		}
	}
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
