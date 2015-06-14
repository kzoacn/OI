#include<bits/stdc++.h>
#include<ext/rope>
using namespace std;
using namespace __gnu_cxx;
rope<set<int> >R;
int main(){
	set<int>S;
	for(int i=1;i<=1e3;i++)S.insert(i);
	for(int i=1;i<=1e3;i++)R.push_back(S);
	cerr<<clock()/double(CLOCKS_PER_SEC)<<endl;
	rope<set<int> >tmp;
	for(int i=1;i<=1e3;i++)tmp=R.substr(0,rand()%R.size());
	cerr<<clock()/double(CLOCKS_PER_SEC)<<endl;
	return 0;
}
