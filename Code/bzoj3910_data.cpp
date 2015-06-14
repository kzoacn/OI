#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
int main(){
	int n=10,m=10;
	printf("%d %d %d\n",n,m,1);
	Lrand R;R.println(R.tree(n));
	while(m--)printf("%d\n",R.range(1,n+1));
	return 0;
}
