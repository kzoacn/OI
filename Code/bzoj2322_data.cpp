#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
int n,m,q;
int main(){
	srand(time(0)^_getpid());
	Lrand R;
	n=500,m=2000,q=2000;
	printf("%d %d %d\n",n,m,q);
	R.println(R.graph_weight(n,m,1024));
	static int a[20001];
	for(int i=1;i<=m;i++)a[i]=i;
	random_shuffle(a+1,a+1+m);
	for(int i=1;i<=q;i++)printf("%d\n",a[i]);
	return 0;
}
