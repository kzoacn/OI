#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
	freopen("bzoj4105.in","w",stdout);
	srand(time(0)^getpid());
	int n=100000,m=100000,p=9977;
	printf("%d %d %d\n",n,m,p);
	for(int i=1;i<=n;i++)printf("%d%c",range(0,p)," \n"[i==n]);
	while(m--){
		int l=1,r=n;
		if(l>r)swap(l,r);
		printf("%d %d %d\n",rand()%2,l,r);
	}
	return 0;
}
