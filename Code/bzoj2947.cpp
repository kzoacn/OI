#include<bits/stdc++.h>
using namespace std;
int getint(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
int n,m;
multiset<int>S;
int main(){
	n=getint();
	long long ans=0;
	while(n--){
		m=getint();
		while(m--)S.insert(getint());
		ans+=*(--S.end())-*S.begin();
		S.erase(--S.end());
		S.erase(S.begin());
	}cout<<ans<<endl;
	return 0;
}
