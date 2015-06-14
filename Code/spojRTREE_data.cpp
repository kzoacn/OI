#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
int main(){
	int n=2000,m=2000;
	printf("%d\n",n);
	Lrand R;R.println(R.tree(n));printf("%d\n",R.range(1,n+1));
	printf("%d\n",m);
	while(m--){printf("%d\n",R.range(1,n+1));}
	return 0;
}
