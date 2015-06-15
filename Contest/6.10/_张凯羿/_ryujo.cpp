#include<cstdio>
#include<vector>
#include<cctype>
#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=100010;
template<typename T>
T in(){
	T r=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r*f;
}
int n,m;
int a[maxn];
struct edge{int u,v,w;};
vector<edge>G[maxn];
int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn],mp[maxn],rmp[maxn],z;
void dfs(int u){
	siz[u]=1;
	for(int i=0;i<G[u].size();i++){
		edge e=G[u][i];
		if(fa[u]==e.v)continue;
		dep[e.v]=dep[u]+1;fa[e.v]=u;
		dfs(e.v);
		siz[u]+=siz[e.v];
		if(!a[e.v]&&siz[son[u]]<siz[e.v])son[u]=e.v;
	}if(a[u])son[u]=0;
}
void build(int u,int tp){
	mp[u]=++z;rmp[z]=u;top[u]=tp;
	if(son[u])build(son[u],tp);
	for(int i=0;i<G[u].size();i++){
		edge e=G[u][i];
		if(e.v!=fa[u]&&e.v!=son[u])build(e.v,e.v);
	}
}
namespace BF{	
	int mp[101][101];
	int calc(int s){
		int ans=0;
		for(int i=1;i<=n;i++){
			int flag=1;
			for(int j=n;j>=1;j--)if(a[j]){
				if(mp[j][i]<mp[s][i]||(mp[j][i]==mp[s][i]&&j<s)){
					flag=0;break;
				}
			}ans+=flag;
		}return ans;
	}
	void solve(){
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)mp[i][j]=1e9;
		for(int i=1;i<=n;i++)mp[i][i]=0;
		for(int i=1;i<n;i++){
			int u=in<int>(),v=in<int>(),w=in<int>();
			mp[u][v]=mp[v][u]=w;
			G[u].push_back((edge){u,v,w});
			G[v].push_back((edge){v,u,w});			
		}
		for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		mp[i][j]=min(mp[i][j],mp[i][k]+mp[k][j]);
		for(int i=1;i<=n;i++)a[i]=in<int>();		
		int ans=0;
		for(int i=1;i<=n;i++)if(!a[i])
			ans=max(ans,calc(i));
		cout<<ans<<endl;
	}
}
int main(){
	freopen("ryujo.in","r",stdin);
	n=in<int>();
	BF::solve();
	return 0;
}
