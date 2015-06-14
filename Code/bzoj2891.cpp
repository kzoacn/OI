#include<bits/stdc++.h>
using namespace std;
double drand(){return rand()/double(RAND_MAX);}
int n,m;
int w[7][101];
double mp[7][101];
int Link[101],vis[101];
void gen(){
	memset(Link,0,sizeof Link);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	if(drand()<mp[i][j])w[i][j]=1;
	else w[i][j]=0;
}
int TT=0;
int find(int u){
	for(int i=1;i<=m;i++)if(w[u][i]){
		if(vis[i]==TT)continue;
//		vis[i]=TT;
		if(!Link[i]){
			Link[i]=u;return 1;
		}
	}
	for(int i=1;i<=m;i++)if(w[u][i]){
		if(vis[i]==TT)continue;
		vis[i]=TT;
		if(find(Link[i])){
			Link[i]=u;return 1;
		}
	}
	
	return 0;
}
int match(){
	int ans=0;
	for(int i=1;i<=n;i++){
		TT++;
		ans+=find(i);
	}return ans;
}
int main(){
	srand(19981223);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)scanf("%lf",&mp[i][j]);
	double _T=6e4;
	int T=_T;
	double ans=0;
	while(T--)
		gen(),
		ans+=match()/_T;
	printf("%.2lf",ans);
	return 0;
}
