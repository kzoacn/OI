#include<bits/stdc++.h>
using namespace std;
const int maxn=10010;
vector<int>G[maxn],Ge[maxn];
int low[maxn],dfn[maxn],z,ins[maxn];
stack<int>S;
int mp[maxn],s,t,n,m,cnt,bel[maxn];
double a[101][101];
vector<int>vec[maxn];
double f[maxn];
short vis[maxn],cal[maxn];
int dcmp(double x){return (x>1e-9)-(x<-1e-9);}
void Gauss(int n){
	for(int i=0;i<n;i++){
		int r=i;
		for(int j=i+1;j<n;j++)if(fabs(a[j][i])>fabs(a[r][i]))r=j;
		for(int j=0;j<=n;j++)swap(a[r][j],a[i][j]);
		for(int j=i+1;j<n;j++){
			double t=a[j][i]/a[i][i];
			for(int k=i;k<=n;k++)
				a[j][k]-=t*a[i][k];
		}
	}
	for(int i=n-1;i>=0;i--){
		for(int j=i+1;j<n;j++)a[i][n]-=a[j][n]*a[i][j];
//		if(!dcmp(a[i][i])){puts("INF");exit(0);}
		a[i][n]/=a[i][i];
	}
}
void tarjan(int u){
	dfn[u]=low[u]=++z;S.push(u);ins[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(ins[v])low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		cnt++;int v;
		do{
			v=S.top();S.pop();
			ins[v]=0;bel[v]=cnt;
			vec[cnt].push_back(v);
		}while(v!=u);
	}
}
void calc(int x){
	int z=0,n=vec[x].size();
	for(int i=0;i<n;i++)mp[vec[x][i]]=i;
	for(int i=0;i<n;i++)for(int j=0;j<=n;j++)a[i][j]=0;
	for(int i=0;i<n;i++){
		a[i][i]=a[i][n]=G[vec[x][i]].size();double siz=G[vec[x][i]].size();
		a[i][i]=max(a[i][i],1.);
		for(int v,j=0;j<G[vec[x][i]].size();j++){
			v=G[vec[x][i]][j];
			if(!cal[v])
				a[i][mp[v]]+=-1;
			else a[i][n]+=f[v];
		}
	}Gauss(n);
	for(int i=0;i<n;i++)f[vec[x][i]]=a[i][n],cal[vec[x][i]]=1;
}
void dfs(int u){
	vis[u]=1;
	for(int v,i=0;i<Ge[u].size();i++){
		if(!vis[v=Ge[u][i]])
			dfs(v);
	}calc(u);
}
bool vis2[maxn];
int dfs2(int u){
	int ans=1;vis2[u]=1;
	for(int i=0;i<Ge[u].size();i++){
		int	v=Ge[u][i];
		if(!vis2[v])
			ans+=dfs2(v);
	}return ans;
}
bool vis3[maxn];
int dfs3(int u){
	int ans=1;vis3[u]=1;
	for(int i=0;i<G[u].size();i++){
		int	v=G[u][i];
		if(!vis3[v])
			ans+=dfs3(v);
	}return ans;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		Ge[v].push_back(u);
//		if(u==s&&v==t){puts("INF");return 0;}
		G[u].push_back(v);
	}//if(dfs2(t)!=dfs3(s)){puts("INF");return 0;}
	//if(G[s].size()==1&&G[s][0]==t){puts("INF");return 0;}
	dfs2(t);dfs3(s);
	for(int i=1;i<=n;i++)if(!vis2[i]&&vis3[i]){puts("INF");return 0;}
	G[t].clear();
	for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
	for(int i=1;i<=n;i++)Ge[i].clear();
	for(int i=1;i<=n;i++)for(int v,j=0;j<G[i].size();j++){
		if(bel[i]!=bel[v=G[i][j]])
		Ge[bel[i]].push_back(bel[v]);
	}dfs(bel[s]);
	printf("%.3lf\n",f[s]);
	return 0;
}
