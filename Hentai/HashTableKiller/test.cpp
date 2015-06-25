#include<bits/stdc++.h>
#include<ext/hash_set>
using namespace std;
unordered_set<int>ht;
int main(){
	freopen("in3","r",stdin);
	set<int>S;
	int n;//scanf("%d",&n);
	long long x;
	while(cin>>x){
		ht.insert(x);
		//cerr<<ht.bucket_count()<<endl;
	}
//	for(set<int>::iterator it=S.begin();it!=S.end();it++)
///		cout<<*it<<endl;
	return 0;
}
