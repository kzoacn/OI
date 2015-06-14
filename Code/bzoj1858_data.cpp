#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
int n=100,m=10;
int main(){
	printf("%d %d\n",n,m);
	Lrand R;
	R.print(R.sequence(n,2,true));
	while(m--){
		int op=R.range(0,5);
		printf("%d ",op);
		R.print(R.interval(n-1));
	}
	return 0;
}
