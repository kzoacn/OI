#include<bits/stdc++.h>
using namespace std;
double calc(double d,double p){
	double ans=0;
	ans+=(d-1)/d*p*(1/d);
	ans+=(d-1)/d*p/d*(d-2);
//	p=0;
	ans+=(d-1)/d*(1-p)/(d-2);
	return ans;
}
void sol(){
	double d;
	double p;
	cin>>d>>p;
	printf("%.10f\n",calc(d,p));
}
int main(){
	freopen("u1.in","r",stdin);
//	freopen("u2.out","w",stdout);
	int T;cin>>T;
	while(T--)sol();
	return 0;
}
