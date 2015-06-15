#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
	srand(time(0)^getpid());
	int n=5,m=5;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)printf("%d%c",range(1,16)," \n"[i==n]);
	for(int i=1;i<=n;i++)printf("%d%c",range(1,16)," \n"[i==m]);
	int q=range(1,3);
	printf("%d\n",q);
	while(q--){
		int l=range(1,n+1),r=range(1,n+1);
		if(l>r)swap(l,r);
		int x=r-l+1;
		printf("%d %d ",l,r);
		l=range(1,n+1),r=range(1,n+1);
		if(l>r)swap(l,r);
		x*=(r-l+1);printf("%d %d %d\n",l,r,range(1,x+1));	
	}
	return 0;
}
