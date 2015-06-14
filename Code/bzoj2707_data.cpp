#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
int main(){
	int n=100,m=180;	Lrand R;
	int s=R.range(1,n+1),t=R.range(1,n+1);
	printf("%d %d %d %d\n",n,m,s,t);
	for(int i=1;i<n;i++)printf("%d %d\n",i,i+1);
	R.println(R.digraph(n,m-n+1));
	return 0;
}
