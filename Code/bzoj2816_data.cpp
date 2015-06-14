#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
int n=16,m=15,c=3,k=100;
int main(){
	Lrand R;
	printf("%d %d %d %d\n",n,m,c,k);
	for(int i=1;i<=n;i++)printf("%d%c",R.range(1,5)," \n"[i==n]);
	for(int i=2;i<=n;i++)
	printf("%d %d %d\n",i,R.range(1,i),R.range(0,c));
	while(k--){
		int op=rand()%3;
		printf("%d ",op);
		if(op==0){
			printf("%d %d\n",R.range(1,n+1),R.range(1,5));
		}else if(op==1){
			printf("%d %d %d\n",R.range(1,n+1),R.range(1,n+1),R.range(0,c));
		}else{
			printf("%d %d %d\n",R.range(0,c),R.range(1,n+1),R.range(1,n+1));
		}
	}
	return 0;
}
