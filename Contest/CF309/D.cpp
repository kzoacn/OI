#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+4;
int n,m,k;
int whi[maxn],in[maxn],vis[maxn],out[maxn];
double ans=-1;
vector<int>anss;
int sta[maxn],top;
vector<int>G[maxn];
void dfs(int u){
	vis[u]=1;sta[++top]=u;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(vis[v]||whi[v])continue;
		dfs(v);
	}
}
int dcmp(double x){return (x>1e-12)-(x<-1e-12);}
double K[maxn];
struct cmp{
	bool operator()(int x,int y){
		return dcmp(K[x]-K[y])?K[x]<K[y]:x<y;
	}
};
set<int,cmp>S;
void calc(int s){
	top=0;dfs(s);S.clear();
	for(int i=1;i<=top;i++){
		int u=sta[i];
		for(int j=0;j<G[u].size();j++){
			int v=G[u][j];
			if(!whi[v])out[u]++;
		}K[u]=(double)out[u]/in[u];		
		S.insert(u);
	}
	while(!S.empty()){
		int u=*S.begin();
		if(K[u]>ans){
			ans=K[u];anss.clear();
			for(set<int>::iterator it=S.begin();it!=S.end();it++)
			anss.push_back(*it);
		}S.erase(S.begin());
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];if(whi[v])continue;
			if(S.find(v)==S.end())continue;
			S.erase(v);
			out[v]--;K[v]=(double)out[v]/in[v];	
			S.insert(v);
		}
	}
}
int main(){
	freopen("D.in","r",stdin);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++){
		int x;scanf("%d",&x);
		whi[x]=1;
	}
	for(int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		in[u]++;in[v]++;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;i++)if(!vis[i]&&!whi[i]){
		if(!in[i])continue;
		calc(i);
	}
//	printf("%.2lf\n",ans);
	cout<<anss.size()<<endl;
	for(int i=0;i<anss.size();i++)
	printf("%d%c",anss[i]," \n"[i+1==anss.size()]);
	return 0;
}
