#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int n=100000,m=100000;
int range(int l,int r){return rand()%(r-l)+l;}
void ranP(){
	printf("%d %d %d",range(1,400),range(1,400),range(1,400));
}
int main(){
srand(time(0)^getpid());
	printf("%d\n",n);
	while(n--)
	ranP(),puts("");
	printf("%d\n",m);
	while(m--){
		int ty=rand()%2;
		if(ty){
			printf("ADD ");ranP();puts("");
		}else{
			printf("QUERY ");ranP();printf(" %d",range(200,600));puts("");
		}
	}
	return 0;
}
