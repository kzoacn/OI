#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#define m_p make_pair
using namespace std;
const int maxn=2e5+5;
typedef long long LL;
vector<pair<int,int> >G[maxn];
int n,vis[maxn],pre[maxn],ans;
LL d[maxn],cur;
int flag,W[maxn];
void dfs(int u,int fa){
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i].first,w=G[u][i].second;
		if(v==fa||vis[v])continue;
		d[v]=d[u]+w;pre[v]=u;vis[v]=flag;W[v]=w;
		if(d[v]>d[ans])ans=v;
		dfs(v,u);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		G[u].push_back(m_p(v,w));
		G[v].push_back(m_p(u,w));
	}dfs(1,0);int A=ans;
	d[A]=ans=0;dfs(A,0);int B=ans;
	for(int i=B;i!=A;i=pre[i])vis[i]=1;vis[A]=1;
	LL len=d[ans],L=0;
	cout<<len<<endl;
	int res,f=1;
	for(;B!=A;){
		L+=W[B];
		B=pre[B];
		d[B]=ans=0;
		dfs(B,0);
		if(d[ans]==L&&f)res=0;//,f=0;
		else res++;
		if(d[ans]==len-L)break;		
	}cout<<res<<endl;
	return 0;
}
