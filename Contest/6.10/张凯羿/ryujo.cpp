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
const int BIT=18;
struct edge{int u,v,w;};
vector<edge>G[maxn];
int fa[maxn][BIT],dep[maxn],siz[maxn],son[maxn],top[maxn],mp[maxn],rmp[maxn],z,d[maxn][BIT];
void make(int u){
	for(int i=1;i<BIT;i++)if(fa[u][i-1])
		fa[u][i]=fa[fa[u][i-1]][i-1],
		d[u][i]=d[u][i-1]+d[fa[u][i-1]][i-1];
}
void dfs(int u){
	siz[u]=1;make(u);
	for(int i=0;i<G[u].size();i++){
		edge e=G[u][i];
		if(fa[u][0]==e.v)continue;
		dep[e.v]=dep[u]+1;fa[e.v][0]=u;d[e.v][0]=e.w;
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
		if(e.v!=fa[u][0]&&e.v!=son[u])build(e.v,e.v);
	}
}
namespace BF{	
	int mp[101][101];
	int calc(int s){
		int ans=0;
		for(int i=1;i<=n;i++){
			int u=0;
			for(int j=n;j>=1;j--)if(a[j]){
				if(mp[j][i]<=mp[u][i]||!u)
					u=j;
			}
			if(mp[u][i]==mp[s][i])ans+=s<=u;
			else ans+=mp[s][i]<mp[u][i];
		}return ans;
	}
	void solve(){
		static int mp[101][101];
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
int mn[maxn];
int dis(int u,int v){
	int ans=0;
	if(dep[u]<dep[v])swap(u,v);
	int D=dep[u]-dep[v];
	for(int i=0;i<BIT;i++)if(D>>i&1)
		ans+=d[u][i],u=fa[u][i];
	if(u==v)return ans;
	for(int i=BIT-1;i>=0;i--)if(fa[u][i]!=fa[v][i])
		ans+=d[u][i]+d[v][i],u=fa[u][i],v=fa[v][i];
	ans+=d[u][0]+d[v][0];
	return ans;
}
int T;
int calc(int s){
	T++;
	static int vis[maxn];
	queue<int>q;q.push(s);
	vis[s]=T;
	vector<int>good,bad;
	while(!q.empty()){
		int u=q.front();q.pop();
		good.push_back(u);
		for(int i=0;i<G[u].size();i++){
			edge e=G[u][i];
			if(vis[e.v]==T)continue;
			vis[e.v]=T;
			if(a[e.v])bad.push_back(e.v);
			else q.push(e.v);	
		}
	}int ans=0;
	for(int i=0;i<good.size();i++){
		int d1=dis(s,good[i]);
		int flag=1;
		for(int j=0;j<bad.size();j++){
			int d2=dis(good[i],bad[j]);
			if(d2<d1||(d2==d1&&bad[j]<s)){
				flag=0;break;
			}
		}ans+=flag;
	}return ans;
}
int compute(int l,int r){
	int ans=0;
	ans=max(calc(rmp[l]),calc(rmp[r]));
	while(r-l>40){
		int mid1=l+(r-l)/3;
		int mid2=r-(r-l)/3;
		int ll=calc(rmp[mid1]);
		int rr=calc(rmp[mid2]);
		ans=max(ans,ll);ans=max(ans,rr);
		if(ll>rr)
			r=mid2;
		else l=mid1;
	}for(int i=l;i<=r;i++)ans=max(ans,calc(rmp[i]));
	return ans;
}
bool cmp(int x,int y){
	return dep[mn[x]]-dep[x]>dep[mn[y]]-dep[y];
}
void solve(){
	for(int i=1;i<n;i++){
		int u=in<int>(),v=in<int>(),w=in<int>();
		G[u].push_back((edge){u,v,w});
		G[v].push_back((edge){v,u,w});			
	}	
	for(int i=1;i<=n;i++)a[i]=in<int>();
	dfs(1);build(1,1);
	for(int i=n;i>=1;i--){
		if(!mn[top[i]]||dep[i]>dep[mn[top[i]]])
			mn[top[i]]=i;
	}
	static int _top[maxn];
	for(int i=1;i<=n;i++)_top[i]=top[i];
	sort(_top+1,_top+1+n);
	int size=unique(_top+1,_top+1+n)-_top-1;
	sort(_top+1,_top+1+size,cmp);
	int ans=0;
	for(int i=1;i<=size;i++){
		if(clock()/double(CLOCKS_PER_SEC)>2.8)break;
		if(!a[_top[i]])
			ans=max(ans,compute(mp[_top[i]],mp[mn[_top[i]]]));
	}
	cout<<ans<<endl;
}
int main(){
	freopen("ryujo.in","r",stdin);
	freopen("ryujo.out","w",stdout);
	n=in<int>();
	if(n<=100)
		BF::solve();
	else solve();
	return 0;
}
