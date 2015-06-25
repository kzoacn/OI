#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+6;
int n,m,p,q;
pair<int,int> a[maxn];
set<int>S;
int main(){
	cin>>n>>m>>p>>q;
//	n=1e5;m=1e7;p=10,q=5;
	for(int i=1;i<=m;i++){
		int l=(i*p+q)%n+1;
		int r=(i*q+p)%n+1;
		if(l>r)swap(l,r);
		vec[l].push_back(i);
		vec[r+1].push_back(-i);
	}
	cerr<<"done"<<endl;
	S.insert(0);
	for(int i=1;i<=n;i++){
		if(i%10000==0)cerr<<i<<endl;
		for(int j=0;j<vec[i].size();j++){
			int x=vec[i][j];
			if(x<0)S.erase(-x);
			else S.insert(x);
		}
	//	printf("%d\n",*S.rbegin());
	}
	
	return 0;
}
