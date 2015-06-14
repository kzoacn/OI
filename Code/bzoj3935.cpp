#include<bits/stdc++.h>
using namespace std;
int dcmp(double x){return (x>1e-6)-(x<-1e-6);}
double a[1050][550];
int n,m;
int C[505],x;
void pivot(int l,int e){
	for(int i=0;i<=n;i++)if(i!=e)
		a[l][i]/=a[l][e];
	a[l][e]=1/a[l][e];
	for(int i=0;i<=m;i++)if(i!=l){
		if(!dcmp(a[i][e]))continue;
		for(int j=0;j<=n;j++)if(j!=e)
			a[i][j]-=a[i][e]*a[l][j];
		a[i][e]*=-a[l][e];
	}
}
double simplex(){
	while(1){
		int l=1,e=1;
		for(int i=1;i<=m;i++)if(a[i][0]<a[l][0])l=i;
		if(dcmp(a[l][0])>=0)break;
		for(int i=1;i<=n;i++)if(a[l][i]<a[l][e])e=i;
		if(dcmp(a[l][e])>=0){puts("-1");exit(0);}
		pivot(l,e);
	}
	while(1){
		int l=1,e=1;
		for(int i=1;i<=n;i++)if(a[0][i]>a[0][e])e=i;
		if(dcmp(a[0][e])<=0)return -a[0][0];
		for(int i=1;i<=m;i++)if(dcmp(a[i][e])>0&&a[i][0]*a[l][e]<a[i][e]*a[l][0])l=i;
		if(dcmp(a[l][e])<=0){puts("-1");exit(0);}
		pivot(l,e);
	}
}
vector<pair<int,int> >G[505];
int d[505];
void bfs(int s,double a[550]){
	queue<int>q;q.push(s);a[s]=-1;d[s]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i].first,w=G[u][i].second;
			if(a[v]||d[u]+w>x)continue;
			a[v]=-1;d[v]=d[u]+w;q.push(v);
		}
	}
}
int main(){
	scanf("%d%d",&n,&x);
	for(int i=1;i<=n;i++)scanf("%d",&C[i]);
	for(int i=1;i<n;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		G[u].push_back(make_pair(v,w));
		G[v].push_back(make_pair(u,w));
	}m=n;
	for(int i=1;i<=n;i++)
		a[0][i]=-(!C[i]);
	for(int i=1;i<=n;i++)
		bfs(i,a[i]),a[i][0]=-1;
	m++;
	for(int i=1;i<=n;i++)
		a[m][i]=1;a[m][0]=accumulate(C+1,C+1+n,0);
	m++;
	for(int i=1;i<=n;i++)
		a[m][i]=-1;a[m][0]=-accumulate(C+1,C+1+n,0);
	for(int i=1;i<=n;i++)
		m++,a[m][i]=1,a[m][0]=1;			
	int ans=-simplex()+.5;
	cout<<ans<<endl;
	return 0;
}
