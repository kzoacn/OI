#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k;
	cin>>n>>k;
	if(n==1)puts("1");
	else cout<<min(k,n-k+1)*2<<endl;
	return 0;
}
