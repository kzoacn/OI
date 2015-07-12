#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("B.in","w",stdout);
	srand(time(0));
	int n=2500,m=5000;
	int T=1;
	printf("%d\n",T);
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
		printf("%d%c",rand()%10000-5000," \n"[i==n]);
	for(int i=1;i<=m;i++)
		printf("%d%c",rand()%10000-5000," \n"[i==n]);
	return 0;
}
