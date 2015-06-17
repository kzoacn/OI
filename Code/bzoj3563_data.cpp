#include<bits/stdc++.h>
#include<unistd.h>
#include<Lrand.h>
using namespace std;
int n=4,m=5;
int range(int l,int r){return rand()%(r-l)+l;}
Lrand R;
int main(){
	srand(time(0)^getpid());
	printf("%d %d\n",n,m);	
	R.println(R.graph(n,m));
	int q=3;
	printf("%d\n",q);
	while(q--){
		int k=range(1,4);
		printf("%d ",k);
		while(k--)printf("%d ",range(1,m+1));
		puts("");
	}
	return 0;
}
