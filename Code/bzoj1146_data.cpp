#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("bzoj1146.in","w",stdout);
	int n=20,m=20;
	srand(time(0));
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)printf("%d%c",rand()%10," \n"[i==n]);
	for(int i=2;i<=n;i++)
		printf("%d %d\n",i,rand()%(i-1)+1);
	while(m--)
		printf("%d %d %d\n",rand()%n,rand()%n+1,rand()%n+1);
	return 0;	
} 
