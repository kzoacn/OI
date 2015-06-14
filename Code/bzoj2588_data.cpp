#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
int n=100,m=100;
int main(){
	printf("%d %d\n",n,m);
	Lrand R;R.print(R.sequence(n,1000));
	R.println(R.tree(n));
	while(m--)printf("%d %d %d\n",R.range(1,n),R.range(1,n),R.range(1,4));
	return 0;
}
