#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
int main(){
	Lrand R;
	int n=5;
	cout<<n<<endl;
	while(n--)cout<<R.range(-10,10)<<" ";
	//R.print(R.sequence(n,-10,10));
	return 0;
}
