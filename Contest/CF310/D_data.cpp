#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int n=4,m=3;
int ran[2333];
int range(int l,int r){return rand()%(r-l)+l;}
int len=10;
int main(){
	srand(time(0)^getpid());
	for(int i=1;i<len;i++)ran[i]=i*2;
	random_shuffle(ran+1,ran+len);
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)printf("%d%c",ran[i]," \n"[i==n]);
	while(m--){
		printf("%d %d\n",range(1,n+1),range(1,len*10));
	}
	return 0;
}
