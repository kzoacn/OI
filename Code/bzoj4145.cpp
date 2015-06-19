#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int n,m;
LL d[101];
LL f[1<<16],g[1<<16],c[16];
LL calc(int S){
	LL ans=0;
	for(int i=0;i<m;i++)if(S>>i&1)
		ans+=c[i];
	return ans;
}
int main(){
//	freopen("bzoj4145.in","r",stdin);
	cin>>n>>m;
	for(int S=0;S<(1<<m);S++)f[S]=g[S]=1e15;f[0]=g[0]=0;
	for(int i=0;i<n;i++){
		cin>>d[i];
		for(int j=0;j<m;j++)cin>>c[j];
		for(int S=0;S<(1<<m);S++){
			f[S]=min(f[S],calc(S)+d[i]);
		}
	}
	for(int i=0;i<(1<<m);i++)
	for(int j=i;;j=i&(j-1)){
		g[i]=min(g[i],g[j]+f[i^j]);
		 if(!j)break;
	}cout<<g[(1<<m)-1]<<endl;
	return 0;
}
