#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int n,m;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
	srand(time(0)^getpid());
	n=8;
	printf("%d\n",n);
	while(n--)printf("%d %d\n",range(-5,5),range(-5,5));
	return 0;
}
