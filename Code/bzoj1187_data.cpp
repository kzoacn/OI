#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int n=100,m=6;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
	freopen("bzoj1187.in","w",stdout);
	srand(time(0)^getpid());
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
		printf("%d%c",range(-1000,1000)," \n"[j==n]);
	return 0;
}
