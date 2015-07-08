#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=1e6+2;
typedef long long LL;
int n,mo;
vector<int>G[maxn];
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
int f[maxn][2],g[maxn][2];
int pf[maxn],sf[maxn];
int pg[maxn],sg[maxn];
int fa[maxn],tmp[maxn];
void dfs(int u){
	f[u][0]=0;f[u][1]=0;
	g[u][0]=1;
	g[u][1]=0;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==fa[u])continue;
		fa[v]=u;
		dfs(v);
	}
	tmp[0]=0;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==fa[u])continue;
		tmp[++tmp[0]]=v;
	}
	pg[0]=sg[tmp[0]+1]=1;
	pf[0]=sf[tmp[0]+1]=0;
	for(int i=1;i<=tmp[0];i++){
		int v=tmp[i];
		pf[i]=pf[i-1]+max(f[v][0],f[v][1]);
		if(f[v][0]==f[v][1])
			pg[i]=(LL)pg[i-1]*(g[v][0]+g[v][1])%mo;
		else pg[i]=(LL)pg[i-1]*(f[v][0]>f[v][1]?g[v][0]:g[v][1])%mo;
	}
	for(int i=tmp[0];i>=1;i--){
		int v=tmp[i];
		sf[i]=sf[i+1]+max(f[v][0],f[v][1]);
		if(f[v][0]==f[v][1])
			sg[i]=(LL)sg[i+1]*(g[v][0]+g[v][1])%mo;
		else sg[i]=(LL)sg[i+1]*(f[v][0]>f[v][1]?g[v][0]:g[v][1])%mo;	
	}
	f[u][0]=pf[tmp[0]];
	g[u][0]=pg[tmp[0]];
	for(int i=1;i<=tmp[0];i++){
		int v=tmp[i];
		if(f[u][1]<pf[i-1]+f[v][0]+sf[i+1]+1){
			f[u][1]=pf[i-1]+f[v][0]+sf[i+1]+1;
			g[u][1]=(LL)pg[i-1]*g[v][0]%mo*sg[i+1]%mo;
		}else if(f[u][1]==pf[i-1]+f[v][0]+sf[i+1]+1){
			g[u][1]+=(LL)pg[i-1]%mo*g[v][0]%mo*sg[i+1]%mo;
			g[u][1]%=mo;
		}
	}
}
int main(){
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
	n=in();
	for(int i=1;i<n;i++){
		int u=in(),v=in();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	scanf("%d",&mo);
	
	dfs(1);
	
	if(f[1][0]==f[1][1])cout<<f[1][0]<<endl<<g[1][0]+g[1][1]<<endl;
	if(f[1][0]>f[1][1])cout<<f[1][0]<<endl<<g[1][0]<<endl;
	if(f[1][0]<f[1][1])cout<<f[1][1]<<endl<<g[1][1]<<endl;
	return 0;
}
