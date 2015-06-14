#include<bits/stdc++.h>
using namespace std;
int n;
struct alien{
	int s,t,r;
}a[305];
int f[605][605],tmp[605],T;
int vis[605][605];
int solve(int l,int r){
	if(vis[l][r])return f[l][r];vis[l][r]=1;
	int ps=-1;
	for(int i=1;i<=n;i++)if(l<a[i].s&&a[i].t<r&&(ps==-1||a[ps].r<a[i].r))ps=i;
	if(ps==-1)return f[l][r]=0;
	f[l][r]=INT_MAX;
	for(int i=a[ps].s;i<=a[ps].t;i++)
		f[l][r]=min(f[l][r],a[ps].r+solve(l,i)+solve(i,r));
	return f[l][r];
}
int main(){
	int _;scanf("%d",&_);
	while(_--){
		scanf("%d",&n);T=0;
		memset(vis,0,sizeof vis);
		for(int i=1;i<=n;i++){
			scanf("%d%d%d",&a[i].s,&a[i].t,&a[i].r);
			tmp[++T]=a[i].s;
			tmp[++T]=a[i].t;
		}sort(tmp+1,tmp+1+T);
		T=unique(tmp+1,tmp+1+T)-tmp-1;
		for(int i=1;i<=n;i++)
			a[i].s=lower_bound(tmp+1,tmp+1+T,a[i].s)-tmp,
			a[i].t=lower_bound(tmp+1,tmp+1+T,a[i].t)-tmp;
		T++;
		cout<<solve(0,T)<<endl;
	}
	return 0;
}
