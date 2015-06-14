#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int n=10,m=10;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
	srand(time(0)^getpid());
	printf("%d\n",m+1);
	while(m--){
		int l=range(1,n+1),r=range(1,n+1);
		if(l>r)swap(l,r);
		int ty=rand()%3+1;
		if(ty==1){
			printf("mul %d %d %d\n",l,r,range(2,10));
		}else if(ty==2){
			printf("add %d %d %d\n",l,r,range(2,10));
		}else if(ty==3){
			printf("mulx %d %d\n",l,r);
		}
	}printf("query %d\n",range(2,4));
	return 0;
}
