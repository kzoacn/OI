#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int n=50,m=50;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
	srand(time(0)^getpid());
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
		printf("%d %d %d\n",range(-100,100),range(-100,100),range(-10,10));
	for(int i=1;i<=m;i++)
		printf("%d %d %d\n",range(-100,100),range(-100,100),range(-100,100));
	return 0;
}
