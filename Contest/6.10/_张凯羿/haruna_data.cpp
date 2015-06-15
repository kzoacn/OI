#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
	freopen("haruna.in","w",stdout);
	srand(time(0)^getpid()); 
	int n=50,m=50;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)printf("%d%c",range(0,6)," \n"[i==n]);
	for(int i=2;i<=n;i++)printf("%d %d\n",i,range(1,i));
	while(m--){
		printf("%d %d %d\n",range(0,2),range(1,n+1),range(1,n+1));
	}
	return 0;
}
