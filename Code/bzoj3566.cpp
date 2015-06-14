#include<bits/stdc++.h>
using namespace std;
const int maxn=500010;
int n;
double f[maxn][2],p[maxn];
struct edge{int u,v;double w;};
vector<edge>G[maxn];
void dp0(int u,int fa){
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i].v;
		if(v!=fa)dp0(v,u);
	}f[u][0]=1-p[u];
	for(int i=0;i<G[u].size();i++){
		edge e=G[u][i];
		if(e.v==fa)continue;
		f[u][0]*=f[e.v][0]+(1-f[e.v][0])*(1-e.w);
	}
}
int dcmp(double x){return (x>1e-8)-(x<-1e8);}
void dp1(int u,int fa){
	for(int i=0;i<G[u].size();i++){
		edge e=G[u][i];
		if(e.v==fa)continue;
		if(dcmp((f[e.v][0]+(1-f[e.v][0])*(1-e.w)))){
			double t=f[u][0]*f[u][1]/(f[e.v][0]+(1-f[e.v][0])*(1-e.w));
			f[e.v][1]=t+(1-t)*(1-e.w);
		}
		dp1(e.v,u);
	}
}
int main(){
	scanf("%d",&n);	
	for(int i=1;i<n;i++){
		int u,v;double w;
		scanf("%d%d%lf",&u,&v,&w);w/=100;
		G[u].push_back((edge){u,v,w});
		G[v].push_back((edge){v,u,w});
	}for(int i=1;i<=n;i++)scanf("%lf",&p[i]),p[i]/=100;
	dp0(1,0);
	f[1][1]=1;
	dp1(1,0);
	double ans=0;
	for(int i=1;i<=n;i++)ans+=1-f[i][0]*f[i][1];
	printf("%.6f\n",ans);
	return 0;
}
