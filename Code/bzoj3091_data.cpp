#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int n=100,m=100;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
//	freopen("bzoj3091.in","w",stdout);
	srand(time(0)^getpid());
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)printf("%d%c",range(1,100)," \n"[i==n]);
	for(int i=2;i<=n;i++)printf("%d %d\n",i,range(1,i));
	while(m--){
		int ty=rand()%4+1;
		printf("%d %d %d ",ty,range(1,n+1),range(1,n+1));
		if(ty==3)printf("%d",range(1,100));puts("");
	}
	return 0;
}

