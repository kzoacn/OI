#include<bits/stdc++.h>
using namespace std;
int mo[]={
11,
23,
47,
97,
199,
409,
823,
1741,
3739,
7517,
15173,
30727,
62233
};
int main(){
	freopen("in2","w",stdout);
	int n=1e4;
//	printf("%d\n",n);
	int cur=0,cnt=mo[cur]/2+1;
	for(int i=1;i<=n;i++){
		printf("%lld\n",(long long)mo[cur]*cnt);
		if(!--cnt){
			cur++;
			cnt=mo[cur]/2;
		}
	}
	return 0;
}
