#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+4;
int n,m,k;
int whi[maxn],in[maxn],vis[maxn],out[maxn],vi[maxn];
double ans=-1;
vector<int>anss;
int sta[maxn],top;
vector<int>G[maxn];
void dfs(int u){
	vis[u]=vi[u]=1;sta[top++]=u;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(vis[v]||whi[v])continue;
		dfs(v);
	}
}
double K[maxn];
bool get(int S,int v){
	for(int i=0;i<top;i++)if(sta[i]==v&&(S>>i&1))return 1;
	return false;
}
void calc(int s){
	memset(vi,0,sizeof vi);
	top=0;dfs(s);
	for(int S=1;S<(1<<top);S++){
		memset(out,0,sizeof out);
		double tmp=1e9;vector<int>an;
		for(int i=0;i<top;i++)if(S>>i&1){
			int u=sta[i];an.push_back(u);
			for(int j=0;j<G[u].size();j++){
				int v=G[u][j];
				if(!whi[v]&&get(S,v))out[u]++;
			}
			tmp=min(tmp,(double)out[u]/in[u]);
		}
		if(tmp>ans){
			ans=tmp;anss=an;
		}		
	}
}
int main(){
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
	printf("%.2lf\n",ans);
//	cout<<anss.size()<<endl;
//	for(int i=0;i<anss.size();i++)
//	printf("%d%c",anss[i]," \n"[i+1==anss.size()]);
	return 0;
}
