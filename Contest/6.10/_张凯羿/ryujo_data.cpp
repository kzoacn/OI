#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
	freopen("ryujo.in","w",stdout);
	srand(time(0)^getpid());
	int n=100;
	printf("%d\n",n);
	for(int i=2;i<=n;i++)
		printf("%d %d %d\n",i,range(max(i-4,1),i),range(1,100));
	for(int i=1;i<=n;i++)printf("%d%c",range(0,10)<1?1:0," \n"[i==n]);
	return 0;
}
