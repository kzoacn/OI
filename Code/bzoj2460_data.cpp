#include<Lrand.h>
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n=1000;Lrand R;
	cout<<n<<endl;
	while(n--)cout<<R.range(0LL,(long long)1e10)<<" "<<R.range(1,1000)<<endl;
	return 0;
}
