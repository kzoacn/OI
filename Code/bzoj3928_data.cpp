#include<bits/stdc++.h>
#include<process.h>
using namespace std;
int n=10;
int main(){
	srand(time(0)^_getpid());
	puts("1");
	printf("%d\n",n);
	while(n--){
		int l=rand()%50+1,r=rand()%50+1,R=rand()%50+1;
		if(l>r)swap(l,r);
		printf("%d %d %d\n",l,r,R);
	}
	return 0;
}
