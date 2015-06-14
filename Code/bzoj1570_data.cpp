#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
int main(){
	int n=50,m=80,T=10;
	printf("%d %d %d\n",n,m,T);
	Lrand R;
	R.println(R.graph_weight(n,m,T));
	return 0;
}

