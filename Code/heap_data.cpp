#include<bits/stdc++.h>
using namespace std;
int cur=1;
int tot=1;
int main(){
	srand(time(0));
	int n=1e5,m=1e6;
	printf("%d %d\n",n,m);
	int size=0;
	while(m--){
		int op=rand()%3;
		if(size==0)op=1;
		if(op==1){
			printf("1 %d\n",(cur++));
			size++;
		}else if(op==2){
			puts("2");size--;
		}else puts("3");
	}
	return 0;
}
