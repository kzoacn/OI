#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int n,L;
int d[maxn],Ans,pre[maxn];
vector<int>G[maxn];
int getint(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}int ans=0;
void dfs(int u,int fa){
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==fa)continue;
		d[v]=d[u]+1;if(d[ans]<d[v])ans=v;
		pre[v]=u;
		dfs(v,u);
	}
}
int vis[maxn];
int dfs(int u){
	vis[u]=1;
	int res=1;
	for(int v,i=0;i<G[u].size();i++){
		if(vis[v=G[u][i]])continue;
		res+=dfs(v);
	}return res;
}
int main(){
	n=getint();L=getint();
	for(int i=1;i<n;i++){
		int u=getint(),v=getint();
		G[u].push_back(v);
		G[v].push_back(u);
	}dfs(1,0);int A=ans;
	d[A]=ans=0;dfs(A,0);int B=ans;
	int res=1;L--;
	for(int i=B;i!=A;i=pre[i])vis[i]=1,res++;vis[A]=1;
	static int vec[maxn],siz;
	for(int i=B;i!=A;i=pre[i]){
		for(int j=0;j<G[i].size();j++){
			int v=G[i][j];
			if(vis[v])continue;
			vec[siz++]=dfs(v);
		}
	}sort(vec,vec+siz,greater<int>());
	res+=accumulate(vec,vec+min(L*2+1,siz),0);
	cout<<res<<endl;
	return 0;
}
