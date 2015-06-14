#include<bits/stdc++.h>
using namespace std;
long long n;
double p;
double ans1,ans2;
int main(){
	cin>>n>>p;
	for(int i=0;i<n;i++){
		int tmp=0;
		for(int j=0;j<n;j++){
			if((i^j)>tmp)tmp=i^j;
		}ans1+=tmp;
	}ans1/=n;
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++){
		ans2+=i^j;
	}ans2/=(double)n*n;
	cout<<ans1*(1-p)+ans2*p<<endl;
	return 0;
}
