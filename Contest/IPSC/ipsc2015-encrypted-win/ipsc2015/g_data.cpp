#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int range(int l,int r){return rand()%(r-l)+l;}
void sol(){
	int n=1000,m=1000,c=400;
	printf("%d %d %d\n",n,c,m);
	for(int i=2;i<=n;i++)
	printf("%d%c",range(1,i)," \n"[i==n]);
	while(m--)
		printf("%d %d %d\n",range(1,n+1),range(0,3),range(0,c)<c/2?0:range(0,c));
}
int main(){
	freopen("g.in","w",stdout);
	srand(time(0)^getpid());
	int T=2;
	printf("%d\n",T);
	while(T--)sol();
	return 0;
}
