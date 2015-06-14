#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long UL;
UL n;
double p;
UL cnt1[64];
double ans1,ans2;
int main(){
	cin>>n>>p;
	for(UL i=0;i<n;i++)
	for(int j=0;j<64;j++)
	cnt1[j]+=i>>j&1;
	UL y=0;
	for(int j=63;j>=0;j--)
	if(cnt1[j]<n-cnt1[j]&&(y|(1UL<<j))<n)
		y|=1UL<<j,ans1+=(1UL<<j)*double(n-cnt1[j])/n;
	else ans1+=(1UL<<j)*double(cnt1[j])/n;
		
	for(int j=63;j>=0;j--){
		double p1=(double)cnt1[j]/n;
		double p2=(double)(n-cnt1[j])/n;
		ans2+=2*p1*p2*(1UL<<j);
	}
	
	cout<<ans1*(1-p)+p*ans2<<endl;
	
	return 0;
}
