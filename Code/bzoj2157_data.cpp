#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
int n=10,m=10;
int main(){
	printf("%d\n",n);
	Lrand R;
	R.println(R.tree_weight(n,10,true));
	printf("%d\n",m);
	while(m--){
		int op=rand()%5;
		if(op==0){printf("N %d %d\n",R.range(1,n-1),R.range(1,n-1));}
		else if(op==1){printf("SUM %d %d\n",R.range(0,n),R.range(0,n));}
		else printf("MAX %d %d\n",R.range(0,n),R.range(0,n));
	}
	return 0;
}
