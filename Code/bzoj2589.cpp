#include<bits/stdc++.h>
using namespace std;
const int maxn=4e4+4;
const int maxK=130;
int K,n,m,a[maxn],w[maxn],siz[maxn],son[maxn],top[maxn],fa[maxn],dep[maxn],rt,lans,dfn[maxn];
vector<int>G[maxn];
int rnd(){
	static int x=233;
	return x=(7*x+5)%40009;
}
void dfs(int u){
	siz[u]=1;
	for(int v,i=0;i<G[u].size();i++){
		if((v=G[u][i])!=fa[u]){
			fa[v]=u;dep[v]=dep[u]+1;dfs(v);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])son[u]=v;
		}
	}
}
void build(int u,int tp){
	top[u]=tp;dfn[++dfn[0]]=u;
	if(son[u])build(son[u],tp);
	for(int v,i=0;i<G[u].size();i++)if((v=G[u][i])!=fa[u]&&v!=son[u])
	build(v,v);
}
int LCA(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		u=fa[top[u]];
	}return dep[u]<dep[v]?u:v;
}
int dis(int u,int v){
	int ans=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		ans+=dep[u]-dep[top[u]]+1;
		u=fa[top[u]];
	}return ans+(dep[u]<dep[v]?dep[v]-dep[u]:dep[u]-dep[v]);
}
int getint(){
	int res=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
int _u[maxK],_v[maxK],cnt[maxK][maxn],anss[maxK],vis[maxK][maxn];
void Xor(int x,int id){
	if(vis[id][x])
		anss[id]-=!--cnt[id][a[x]];
	else anss[id]+=!cnt[id][a[x]]++;	
	vis[id][x]^=1;
}
void pathxor(int u,int v,int id){
	int lca=LCA(u,v);
	while(u!=lca)Xor(u,id),u=fa[u];
	while(v!=lca)Xor(v,id),v=fa[v];
}
int Q(int u,int v){
	int uu,vv,d=1e9,id;
	for(int i=1;i<=K;i++){
		int tmp=dis(u,_u[i])+dis(v,_v[i]);
		if(tmp<d)d=tmp,uu=_u[i],vv=_v[i],id=i;
		tmp=dis(u,_v[i])+dis(v,_u[i]);
		if(tmp<d)d=tmp,uu=_v[i],vv=_u[i],id=i;
	}pathxor(u,uu,id);
	pathxor(v,vv,id);
	int lca=LCA(u,v);
	Xor(lca,id);
	int ans=anss[id];
	Xor(lca,id);
	pathxor(u,uu,id);
	pathxor(v,vv,id);
	return ans;
}
int main(){
	scanf("%d%d",&n,&m);
	K=ceil(sqrt((double)n*m/(1*n+m*log(n))));
//	cerr<<K;
	for(int i=1;i<=n;i++)a[i]=getint(),w[i]=a[i];
	sort(w+1,w+1+n);int _n=unique(w+1,w+1+n)-w-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(w+1,w+1+_n,a[i])-w;
	for(int i=1;i<n;i++){
		int u=getint(),v=getint();
		G[u].push_back(v);
		G[v].push_back(u);
	}rt=rnd()%n+1;
	dfs(rt);build(rt,rt);	
	for(int i=1;i<=K;i++){
		_u[i]=dfn[max(n/K*i,1)];_v[i]=dfn[min(n/K*(i+1),n)];
		int u=_u[i],v=_v[i];
		pathxor(u,v,i);
	}
	while(m--){
		int u=getint()^lans,v=getint();
		printf("%d\n",lans=Q(u,v));
	}
	return 0;
}
