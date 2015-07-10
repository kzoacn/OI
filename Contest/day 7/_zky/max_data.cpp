#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int range(int l,int r){return rand()%(r-l)+l;};
int main(){
	freopen("max.in","w",stdout);
	srand(time(0)^getpid());
	int n=1e3,m=1e3;
	printf("%d %d\n",n,m);
	int w=10000,sum=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	printf("%d%c",1," \n"[j==m]);
	return 0;
}
