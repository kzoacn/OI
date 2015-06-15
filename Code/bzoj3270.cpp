#include<bits/stdc++.h>
using namespace std;
int n,m,A,B,tot;
int mp[21][21];
double p[21];
double a[401][401];
vector<int>G[21];
void Gauss(int n){
	
}
void build(){
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		//f[i][j]=(1-p_i)(1-p_j)\sum f[i'][j'] /G[i].sz / G[j].sz
	}
}
int main(){
	scanf("%d%d%d%d",&n,&m,&A,&B);
	for(int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}for(int i=1;i<=n;i++)scanf("%lf",&p[i]);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)mp[i][j]=++tot;
	build();
	Gauss(n);	
	return 0;
}
