#include<bits/stdc++.h>
#define pb push_back
#define m_p make_pair 
using namespace std;
typedef long long LL;
const int maxn=250010;
const int BIT=19;
int n,m;
vector<pair<int,int> >G[maxn];
vector<int>Ge[maxn];
LL mn[maxn];
int fa[maxn][BIT],dep[maxn],z,dfn[maxn],w[maxn],vis[maxn];
void dfs(int u){
	dfn[u]=++z;
	for(int i=1;i<BIT;i++)fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i].first,w=G[u][i].second;
		if(fa[u][0]==v)continue;
		fa[v][0]=u;dep[v]=dep[u]+1;mn[v]=min(mn[u],(LL)w);
		dfs(v);
	}
}
LL dp(int u,int fa){
    LL tmp=0;
    for(int v,i=0;i<Ge[u].size();i++){
    	if((v=Ge[u][i])!=fa)
        tmp+=dp(v,u);
    }Ge[u].clear();
    return tmp?min(tmp,(LL)mn[u]):mn[u];
}
bool cmp(int x,int y){return dfn[x]<dfn[y];}
int h[maxn];
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	int d=dep[u]-dep[v];
	for(int i=BIT-1;i>=0;i--)if(d&(1<<i))u=fa[u][i];
	if(u==v)return u;
	for(int i=BIT-1;i>=0;i--)if(fa[u][i]!=fa[v][i])u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}
int sta[maxn],top;
void add(int u,int v){
	if(u==v)return;
//	cerr<<u<<" "<<v<<endl;
	Ge[u].pb(v);
	Ge[v].pb(u);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		G[u].pb(m_p(v,w));
		G[v].pb(m_p(u,w));
	}mn[1]=1e11;dfs(1);
	scanf("%d",&m);m++;
	while(m-->1){
		int k;scanf("%d",&k);z=1;
		for(int i=1;i<=k;i++)scanf("%d",&h[i]);
		sort(h+1,h+1+k,cmp);z=1;
		for(int i=2;i<=k;i++)if(h[z]!=lca(h[z],h[i]))h[++z]=h[i];
    	top=0;sta[++top]=1;k=z;
    	for(int i=1;i<=k;i++){
       		int u=h[i],f=lca(u,sta[top]);
        	for(;;){
      	      if(dep[f]>=dep[sta[top-1]]){
        	        add(f,sta[top--]);
        	        if(sta[top]!=f)sta[++top]=f;
        	        break;
        	    }add(sta[top-1],sta[top]);top--;
      	 	}if(sta[top]!=u)sta[++top]=u;
    	}while(--top)add(sta[top],sta[top+1]);
		printf("%lld\n",dp(1,0));
	}
	return 0;
}
