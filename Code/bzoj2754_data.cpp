#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
int main(){
	int n=2,m=3;Lrand R;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++){
		int len=R.range(1,7);printf("%d ",len);
		while(len--)printf("%d ",R.range(1,3));
		len=R.range(1,7);printf("%d ",len);
		while(len--)printf("%d ",R.range(1,3));puts("");
	}while(m--){
		int len=R.range(1,7);printf("%d ",len);
		while(len--)printf("%d ",R.range(1,3));
		puts("");
	}
	return 0;
}
