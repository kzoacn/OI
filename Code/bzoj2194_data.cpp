#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
//	freopen("bzoj2194.in","w",stdout);
	srand(time(0)^getpid());
	int n=2;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d %d\n",range(0,4),range(0,4));
	return 0;
}
