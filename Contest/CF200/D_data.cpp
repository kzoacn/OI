#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int n=500,m=500;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
	freopen("D.in","w",stdout);
	srand(time(0)^getpid());
	printf("%d\n",n);
	for(int i=2;i<=n;i++)
		printf("%d %d\n",i,range(1,i));
	printf("%d\n",m);
	while(m--)
		printf("%d %d\n",range(1,4),range(1,n+1));
	return 0;
}
