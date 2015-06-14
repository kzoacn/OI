#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(0)^(long long)(new int));
	int n=10,m=2;
	printf("%d %d\n",n,m+n);
	for(int i=1;i<=n;i++)printf("%d %d\n",i,i);
	while(m--)printf("%d %d\n",rand()%n+1,rand()%n+1);
	return 0;
}
