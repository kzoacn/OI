#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
int main(){
	int n=10;Lrand R;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d %d\n",R.range(1,10),R.range(1,n+1));
	return 0;
}

