#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
struct Heap{
	multiset<int>S;
	int top(){return *S.rbegin();}
	int top2(){return *++S.rbegin();}
	int size(){return S.size();}
	void insert(int x){S.insert(x);};
	void erase(int x){S.erase(S.find(x));}
}A;
vector<int>G[maxn];
namespace HLD{
	int fa[maxn],top[maxn],siz[maxn],son[maxn],mp[maxn],z,dep[maxn];
	void dfs(int u){
		siz[u]=1;
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(v!=fa[u]){
				fa[v]=u;dep[v]=dep[u]+1;
				dfs(v);
				siz[u]+=siz[v];
				if(siz[son[u]]<siz[v])son[u]=v;
			}
		}
	}
	void build(int u,int tp){
		top[u]=tp;mp[u]=++z;
		if(son[u])build(son[u],tp);
		for(int v,i=0;i<G[u].size();i++)if((v=G[u][i])!=son[u]&&v!=fa[u])build(v,v);
	}
	int dis(int u,int v){
		int ans=0;
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]])swap(u,v);
			ans+=dep[u]-dep[top[u]];
			u=fa[top[u]];
		}if(dep[u]<dep[v])swap(u,v);
		return ans+dep[u]-dep[v]+1;
	}
};

int n,m,All;
int f[maxn],siz[maxn],fa[maxn],rt,cant[maxn],tot=1,mp[maxn],cnt;
struct node{
	int f,p;
	Heap D,H;
}t[maxn];

void makert(int u){
	f[u]=0;siz[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==fa[u]||cant[v])continue;
		fa[v]=u;
		makert(v);
		siz[u]+=siz[v];
		f[u]=max(f[u],siz[v]);
	}f[u]=max(f[u],All-f[u]);
	if(f[u]<f[rt])rt=u;
}
int data[maxn],d[maxn],vis[maxn];
void dfs(int u){
	data[++data[0]]=d[u];
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(cant[v]||v==fa[u])continue;
		fa[v]=u;
		d[v]=d[u]+1;
		dfs(v);
	}
}
void calc(int u,int id){
	d[u]=0;data[0]=0;
	dfs(u);
	for(int i=1;i<=data[0];i++)
		t[id].D.insert(data[i]);
}
void solve(int u){
	calc(u,mp[u]);cant[u]=1;t[mp[u]].p=u;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==fa[u]||cant[v])continue;
		f[rt=0]=n+1;All=siz[v];
		mp[v]=++tot;t[mp[v]].f=mp[u];
		solve(v);
		t[mp[u]].H.insert(t[mp[v]].D.top());
	}
	if(t[mp[u]].H.size()>=2)
	A.insert(t[mp[u]].H.top()+t[mp[u]].H.top2());
}
#define f(u) t[u].f
void Rev(int x){
	int u=mp[x];
	if(vis[x]){
		cnt--;
		
	}else{
		cnt++;
		t[u].erase(0);
		while(t[u].f){
			t[f(u)].D.erase(HLD::dis(x,t[f(u)].p));
			
			u=f(u);
		}
	}vis[x]^=1;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	HLD::dfs(1);
	HLD::build(1,1);
	f[rt=0]=n+1;
	mp[rt]=1;
	makert(1);
	scanf("%d",&m);
	while(m--){
		char ty=getchar();
		while(!isalpha(ty))ty=getchar();
		if(ty=='G'){
			if(cnt<=1)printf("%d\n",cnt-1);
			else printf("%d\n",A.top());
		}else{
			int x;scanf("%d",&x);
			Rev(x);
		}
	}
	return 0;
}
