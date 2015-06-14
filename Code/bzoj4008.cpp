#include<bits/stdc++.h>
using namespace std;
double f[221][133];
double p[221];
int d[221];
int T;
int n,m;
void solve(){
	memset(f,0,sizeof f);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lf%d",&p[i],&d[i]);
	f[0][m]=1;double ans=0;
	for(int i=0;i<n;i++)
	for(int j=0;j<=m;j++){
		f[i+1][j]+=f[i][j]*pow(1-p[i+1],j);
		if(j>=1){
			f[i+1][j-1]+=f[i][j]*(1-pow(1-p[i+1],j));
			ans+=f[i][j]*(1-pow(1-p[i+1],j))*d[i+1];
		}
	}
	cout<<fixed<<setprecision(10)<<ans<<endl;
}
int main(){
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
