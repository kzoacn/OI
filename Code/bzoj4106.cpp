#include<bits/stdc++.h>
using namespace std;
double p,a,b,c,d;
int n;
double pr(double k){return p*(sin(a*k+b)+cos(c*k+d)+2);}
int main(){
	cin>>p>>a>>b>>c>>d>>n;
	double mx=0,ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,mx-pr(i));
		mx=max(mx,pr(i));
	}
	printf("%.8lf\n",ans);
	return 0;
}//100 432 406 867 60 1000
