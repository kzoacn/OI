#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
	srand(time(0)^getpid());
	int n=1e5,k=range(0,7);
	printf("%d %d\n",n,k);
	int w=40;
	for(int j=1;j<=n;j++)
	for(int i=1;i<=6;i++)
		printf("%d%c",range(1,w)," \n"[i==6]);
	return 0;
}
