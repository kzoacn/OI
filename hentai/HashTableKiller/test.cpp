#include<bits/stdc++.h>
#include<ext/hash_set>
using namespace std;
__gnu_cxx::hash_set<int>ht;
int main(){
	freopen("in","r",stdin);
	int n;scanf("%d",&n);
	while(n--){
		int x;scanf("%d",&x);
		ht.insert(x);
	}
	return 0;
}
