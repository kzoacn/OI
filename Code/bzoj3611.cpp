#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
const int BIT=21;
int dfn[maxn],n,fa[maxn][BIT],dep[maxn],z;
vector<int>G[maxn];
vector<pair<int,int> >Ge[maxn];
void dfs(int u){
	dfn[u]=++z;
	for(int i=1;i<BIT;i++)if(fa[u][i-1])
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==fa[u][0])continue;
		dep[v]=dep[u]+1;fa[v][0]=u;
		dfs(v);
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	int d=dep[u]-dep[v];
	for(int i=BIT-1;i>=0;i--)if(d>>i&1)u=fa[u][i];
	if(u==v)return u;
	for(int i=BIT-1;i>=0;i--)if(fa[u][i]!=fa[v][i])
		u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}
int dis(int u,int v){
	int ans=0;
	if(dep[u]<dep[v])swap(u,v);
	int d=dep[u]-dep[v];ans=d;
	for(int i=BIT-1;i>=0;i--)if(d>>i&1)u=fa[u][i];
	if(u==v)return ans;
	for(int i=BIT-1;i>=0;i--)if(fa[u][i]==fa[v][i])
		u=fa[u][i],v=fa[v][i],ans+=1<<i<<1;
	return ans;
}
int getn(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
bool bydfn(int x,int y){return dfn[x]<dfn[y];}
int inr[maxn];
void add(int u,int v){
	//Erase[e++]=v;
	int w=dis(u,v);
//	cerr<<u<<" "<<v<<" "<<w<<endl;
	Ge[u].push_back(make_pair(v,w));
	//Ge[v].push_back(make_pair(u,w));
}
int rt;
int _n;
long long s=0,up[maxn],dw[maxn];
int mxx,mnn;
int siz[maxn],d[maxn];
int mx[maxn],mn[maxn];
void dp(int u){
	siz[u]=inr[u];
	mx[u]=inr[u]?0:-1e9;
	mn[u]=inr[u]?0:1e9;
	dw[u]=0;
	for(int i=0;i<Ge[u].size();i++){
		int v=Ge[u][i].first,w=Ge[u][i].second;
		dp(v);
		dw[u]+=(long long)siz[v]*w+dw[v];
   		mxx=max(mxx,mx[u]+mx[v]+w);
		mnn=min(mnn,mn[u]+mn[v]+w);
		mx[u]=max(mx[u],mx[v]+w);
		mn[u]=min(mn[u],mn[v]+w);
		siz[u]+=siz[v];
	}	
}
void dp2(int u){
	for(int i=0;i<Ge[u].size();i++){
		int v=Ge[u][i].first,w=Ge[u][i].second;
		up[v]=(up[u]+dw[u]-dw[v]-(long long)w*siz[v])+(long long)w*(_n-siz[v]);
		dp2(v);
	}Ge[u].clear();
}
void Q(){
	static int a[maxn*2],sta[maxn*2];
	int top=0;
	int k=getn();
	for(int i=0;i<k;i++)a[i]=getn();
	sort(a,a+k,bydfn);
	k=unique(a,a+k)-a;
	sta[top++]=1;_n=k;
	for(int i=0;i<k;i++){
		int LCA=lca(a[i],sta[top-1]);
		while(dep[LCA]<dep[sta[top-1]]){
			if(dep[LCA]>=dep[sta[top-2]]){
				add(LCA,sta[--top]);
				if(sta[top-1]!=LCA)sta[top++]=LCA;
				break;
			}add(sta[top-2],sta[top-1]);top--;
		}if(sta[top-1]!=a[i])sta[top++]=a[i];
	}
	while(top>1)
		add(sta[top-2],sta[top-1]),top--;
	s=0;mxx=INT_MIN;mnn=INT_MAX;
	for(int i=0;i<k;i++)inr[a[i]]=1;
	dp(1);
	dp2(1);
	for(int i=0;i<k;i++)s+=up[a[i]]+dw[a[i]];
	printf("%lld %d %d\n",s/2,mnn,mxx);
	for(int i=0;i<k;i++)inr[a[i]]=0;
}
int main(){
	n=getn();
	for(int i=1;i<n;i++){
		int u=getn(),v=getn();
		G[u].push_back(v);
		G[v].push_back(u);
	}dfs(1);
	int m=getn();
	while(m--)
		Q();
	return 0;
}
