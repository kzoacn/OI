#include<vector>
#include<cstdio>
#include<queue>
#include<iostream>
#include<algorithm>
//#include<ctime>
using namespace std;
const int maxn=40010;
vector<int>G[maxn];
int fa[maxn];
int ans=0;
int sta[maxn],mx[maxn],top,val[maxn],R;
int cl=0;
void dfs(int u,int cur,int mx,int dep){
	cl++;
	if(cl>1.5e7){
		cout<<ans<<endl;
		exit(0);
	}
	cur+=val[u];
	if(cur<0)return;
	mx=max(mx,cur);
	if(ans>mx+(R-dep-cur+1)/2)return;
	if(!cur){
//		if(mx>ans)cerr<<mx<<endl;
		ans=max(ans,mx);
	}
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==fa[u])continue;
		fa[v]=u;
		dfs(v,cur,mx,dep+1);
	}
}
int findR(){
	int T=0;T++;
	static int vis[maxn],d[maxn];
	queue<int>q;q.push(1);d[1]=0;vis[1]=1;
	int A=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(vis[v]==T)continue;
			vis[v]=T;d[v]=d[u]+1;q.push(v);
			if(d[v]>d[A])A=v;
		}
	}
	q.push(A);d[A]=0;vis[A]=++T;
	int ans=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(vis[v]==T)continue;
			vis[v]=T;d[v]=d[u]+1;q.push(v);
			if(d[v]>ans)ans=d[v];
		}
	}
	return ans;
}
int n;
int main(){
	freopen("deep.in","r",stdin);
	scanf("%d",&n);
	for(int i=2;i<=n;i++){
		scanf("%d",&fa[i]);
		G[fa[i]].push_back(i);
		G[i].push_back(fa[i]);
	}mx[0]=-1e9;
	
	for(int i=1;i<=n;i++){
		char s[2];scanf("%s",s);
		val[i]=*s=='('?1:-1;
	}
	
	R=findR();
	
	for(int i=1;i<=n;i++)
		fa[i]=0,dfs(i,0,0,0);
	
	cout<<ans<<endl;
	return 0;
}
