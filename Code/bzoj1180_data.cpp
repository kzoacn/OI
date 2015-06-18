#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
int main(){
	int n=5,m=5;
	Lrand R;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)printf("%d%c",R.range(1,10)," \n"[i==n]);
	printf("%d\n",m);
	while(m--){
		int u=R.range(1,n+1),v=R.range(1,n+1);
		int ty=rand()%3;
		if(ty==0)printf("bridge ");
		if(ty==1)printf("penguins ");
		if(ty==2)printf("excursion ");
		printf("%d %d\n",u,v);
	}
	return 0;
}
