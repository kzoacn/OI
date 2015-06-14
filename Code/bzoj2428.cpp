#include<bits/stdc++.h>
using namespace std;
//const int maxn=1e5+5;
int n,m;
double a[21],xbar;
double b[21];
double sqr(double x){return x*x;}
double calc(){
	double ans=0;	
	for(int i=1;i<=m;i++)
		ans+=sqr(b[i]-xbar);
	ans/=m;
	return sqrt(ans);
}
double ans=1e10;
int main(){
	srand(10086);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i],xbar+=a[i];
	xbar/=m;
	int T=5e5;
	while(T--){
		random_shuffle(a+1,a+1+n);
		for(int i=1;i<=m;i++)b[i]=a[i];
		for(int i=m+1;i<=n;i++)b[min_element(b+1,b+1+m)-b]+=a[i];
		ans=min(ans,calc());
	}printf("%.2lf\n",ans);
	return 0;
}
