#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
int main(){
//	freopen("bzoj1759.in","w",stdout);
	Lrand R;
	int n=1000,m=1000;
	printf("%d\n",n);
	R.println(R.tree(n));
	printf("%d\n",m);
	while(m--){
		int u=R.range(1,n+1);
		int v=R.range(1,n+1);
		int c=R.range(1,8);
		printf("%d %d %d\n",u,v,c);
	}
	return 0;
}
