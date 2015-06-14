#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int n=20,m=20;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
	srand(time(0)^getpid());
	printf("%d %d\n",n,m);
	while(m--){
		int ty=rand()%3+2;
		printf("%d %d\n",ty,range(2,n));
	}
	return 0;
}
