#include<bits/stdc++.h>
using namespace std;
int n=2e5;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
	freopen("bzoj4152.in","w",stdout);
	printf("%d\n",n);
	while(n--){
		printf("%d %d\n",range(1,int(1e9)),range(1,int(1e9)));
	}
	return 0;
}
