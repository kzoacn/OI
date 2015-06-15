#include<bits/stdc++.h>
using namespace std;
int n,m,A,B,tot;
int mp[21][21];
double p[21];
double a[405][405];
vector<int>G[21];
void deb(int n){
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n+1;j++)
		fprintf(stderr,"%.2lf%c",a[i][j]," \n"[j==n+1]);

}
void Gauss(int n){
	
	for(int i=1;i<n;i++){
//		deb(n);	
		int r=i;
		for(int j=i+1;j<=n;j++)if(fabs(a[r][i])<fabs(a[j][i]))r=j;
		for(int j=i;j<=n+1;j++)swap(a[r][j],a[i][j]);
//		deb(n);	
		for(int j=i+1;j<=n;j++){
			double t=a[j][i]/a[i][i];
			for(int k=i;k<=n+1;k++)
				a[j][k]-=t*a[i][k];
//			deb(n);	
		}
	}
//	deb(n);
	for(int i=n;i>=1;i--){
		for(int j=i+1;j<=n;j++)
			a[i][n+1]-=a[j][n+1]*a[i][j];
		a[i][n+1]/=a[i][i];
	}
}
#define sz(x) double(G[x].size())
void build(){
	int m=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
		//f[i][j]=p_ip_jf[i][j]+p_i(\sum f[i][j'] /sz(j))+p_j(\sum f[i'][j] /sz(i))+(1-p_i)(1-p_j)\sum f[i'][j']/sz(i)/sz(j)
		m++;
		if(i!=j)
			a[m][mp[i][j]]=p[i]*p[j]-1;
		else a[m][mp[i][j]]=-1;
		for(int k=0;k<G[i].size();k++)
		for(int l=0;l<G[j].size();l++){
			int u=G[i][k],v=G[j][l];
			if(u!=v)
			a[m][mp[u][v]]=(1-p[u])*(1-p[v])/sz(u)/sz(v);
		}
		for(int k=0;k<G[i].size();k++){
			int u=G[i][k];
			if(u!=j)
			a[m][mp[u][j]]=(1-p[u])*p[j]/sz(u);
		}		
		for(int l=0;l<G[j].size();l++){
			int v=G[j][l];
			if(i!=v)
			a[m][mp[i][v]]=p[i]*(1-p[v])/sz(v);
		}
		if(i==A&&j==B){
			a[m][n*n+1]=-1;
		}
	}
}
int main(){
	freopen("bzoj3270.in","r",stdin);
	scanf("%d%d%d%d",&n,&m,&A,&B);
	for(int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}for(int i=1;i<=n;i++)scanf("%lf",&p[i]);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)mp[i][j]=++tot;
	build();
	Gauss(n*n);	
	for(int i=1;i<=n;i++)printf("%.6lf ",a[mp[i][i]][n*n+1]);
	return 0;
}
