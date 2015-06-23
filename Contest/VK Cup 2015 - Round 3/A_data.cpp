#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
	srand(time(0)^getpid());
	int n=100,m=100;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++){
		int l=range(1,100),r=range(1,100);
		if(l>r)swap(l,r);
		printf("%d %d\n",l,r);
	}
	for(int i=1;i<=m;i++){
		int l=range(1,10),r=range(1,100),c=range(1,100);
		if(l>r)swap(l,r);
		printf("%d %d %d\n",l,r,c);
	}
	
	return 0;
}
