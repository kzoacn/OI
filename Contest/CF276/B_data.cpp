#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int main(){
//	freopen("B.in","w",stdout);
	srand(time(0)^getpid());
	int n=3000;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d%c",rand()%100000+1," \n"[i==n]);
	return 0;
}
