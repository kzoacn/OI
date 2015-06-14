#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
int main(){
	int n=10000,m=10000;
	printf("%d %d\n",n,m);
	Lrand R;R.print(R.sequence(n,n));
	while(m--)printf("%d %d\n",R.range(1,n),R.range(1,n));
	return 0;
}
