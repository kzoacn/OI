#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int main(){
	int q;cin>>q;
	while(q--){
		LL l,r;cin>>l>>r;
		for(int i=0;i<63;i++)if(!(l>>i&1)){
			if((l|(1LL<<i))<=r)
				l|=1LL<<i;
		}cout<<l<<endl;
	}
	return 0;
}
