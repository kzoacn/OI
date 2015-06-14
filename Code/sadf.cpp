#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k,a=0,b=0;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		if(x%2)a++;else b++;
	}
	if(a+b==k){
		puts(abs(a)%2?"Daenerys":"Stannis");
		return 0;
	}
	if(k%2==1){
		if(abs(a-b)<k)
			puts(abs(a-b)%2?"Daenerys":"Stannis");
		else
			puts(a>b?"Stannis":"Daenerys");
	}else{
		if(abs(a-b)<k)
			puts(abs(a-b)%2?"Stannis":"Daenerys");
		else puts("Daenerys");
	}
	return 0;
}
