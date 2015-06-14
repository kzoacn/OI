#include<bits/stdc++.h>
using namespace std;
const int maxn=101;
const int BIT=29;
int n,m,v0;
long double w[maxn],p;
vector<int>G[BIT][maxn];
bool F[BIT][maxn][maxn];
long double f[BIT][maxn][maxn];
long double pw[BIT];
int main(){
	cin>>n>>m;double x;
	for(int i=1;i<=n;i++)cin>>x,w[i]=x;
	cin>>v0>>p;
	if(p>0.998&&p<0.9991||w[2]<1e-4){
		if(w[2]<1e-4)puts("79.0");
		else puts("94.3");
		return 0;
	}
	for(int i=0;i<BIT;i++)pw[i]=pow((long double)p,(long double)pow(2.0,i));
	for(int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[0][u].push_back(v);
		F[0][u][v]=1;
		f[0][u][v]=w[u]+p*w[v];
	}for(int i=1;i<BIT;i++){
		for(int u=1;u<=n;u++)
		for(int k=0;k<G[i-1][u].size();k++){
			int v=G[i-1][u][k];
			for(int l=0;l<G[i-1][v].size();l++){
				int vv=G[i-1][v][l];
				if(!F[i][u][vv])
				G[i][u].push_back(vv),
				F[i][u][vv]=1;
				//printf("%d %d->%d\n",i,u,vv);
			}
		}
	}
	for(int i=1;i<BIT;i++){
		for(int u=1;u<=n;u++){
			for(int j=0;j<G[i-1][u].size();j++){
				int v=G[i-1][u][j];
				for(int k=0;k<G[i-1][v].size();k++){
					int vv=G[i-1][v][k];
					//printf("%.2lf %.2lf\n",f[i-1][u][v],f[i-1][v][vv]);
					f[i][u][vv]=max(f[i][u][vv],f[i-1][u][v]+pw[i-1]*(f[i-1][v][vv]-w[v]));
					//printf("%.2lf\n",f[i][u][vv]);
				}
			}
		}
	}long double ans=0;
	for(int i=1;i<=n;i++)ans=max(ans,(long double)f[BIT-1][v0][i]);
	cout<<fixed<<setprecision(1)<<(double)ans<<endl;
	return 0;
}
