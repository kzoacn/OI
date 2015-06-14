#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
	srand(time(0)^getpid());
	int n=5,m=6;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		putchar(range(1,10)<8?'_':'*');
		if(j==m)puts("");
	}
	return 0;
}
