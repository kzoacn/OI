#include<bits/stdc++.h>
using namespace std;
typedef long long Long;
int H(Long x){
	int h=x^(x>>32);
	 h ^= (h >> 20) ^ (h >> 12);
	return h ^ (h >> 7) ^ (h >> 4);
}
set<Long>S;
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
	freopen("in","w",stdout);
	Long n=4e4;
	Long cur=0,cnt=mo[cur]/2;
	for(Long i=1;i<=n;i++){
		//cerr<<i<<endl;
		Long want=(Long)i*(1<<15);
		Long x=H(want),y=want;
		while(x!=want)y=x,x=H(x);
		cout<<y<<endl;
		cerr<<want<<" "<<H(y)<<endl;
	}
	return 0;
	
}
