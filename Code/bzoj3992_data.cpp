#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
int main(){
	Lrand R;
	int n=R.range(2,5),m=7,x=R.range(1,m),s=R.range(1,m);
	printf("%d %d %d %d\n",n,m,x,s);
	for(int i=0;i<s;i++)printf("%d ",R.range(1,m));
	return 0;
}
