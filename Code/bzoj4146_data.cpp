#include<unistd.h>
#include<bits/stdc++.h>
using namespace std;
int n=10;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
	srand(time(0)^getpid());
	printf("%d\n",n);
	for(int i=1;i<=n;i++)printf("%d%c",range(1,201)," \n"[i==n]);
	return 0;
}
