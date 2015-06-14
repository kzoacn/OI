#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
const int maxn=1e5+5;
pair<int,int> p[maxn];
int main(){
	int n=100,r=50,c=50;Lrand R;
	printf("%d %d %d\n",n,r,c);
	for(int i=1;i<1000;i++)p[i]=make_pair(R.range(1,r),R.range(1,c));
	sort(p+1,p+1000);
	int size=unique(p+1,p+1000)-p;
	random_shuffle(p+1,p+size);
	for(int i=1;i<=n;i++)printf("%d %d %d\n",p[i].first,p[i].second,R.range(1,4));
	return 0;
}
