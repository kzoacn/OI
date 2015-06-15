#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int n=5000;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
	freopen("bzoj4066.in","w",stdout);
	srand(time(0)^getpid());
	int m=200000;
	printf("%d\n",n);
	while(m--){
		int ty=rand()%2+1;
		if(ty==1)printf("%d %d %d %d\n",ty,range(1,n+1),range(1,n+1),range(1,10));
		else {
			int l=range(1,n+1),r=range(1,n+1);
			if(l>r)swap(l,r);
			int ll=range(1,n+1),rr=range(1,n+1);
			if(ll>rr)swap(ll,rr);
			printf("%d %d %d %d %d\n",ty,l,r,ll,rr);
		}
	}puts("3");
	return 0;
}
