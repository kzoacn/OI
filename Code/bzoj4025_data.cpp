#include<bits/stdc++.h>
#include<unistd.h>
//#include<Lrand.h>
using namespace std;
int n=100,m=200,T=200;
set<pair<int,int> >S;
int range(int l,int r){return rand()%(r-l)+l;}
#define par(x,y) make_pair(min(x,y),max(x,y))
int main(){
	freopen("bzoj4025.in","w",stdout);
	srand(time(0)^getpid());
	printf("%d %d %d\n",n,m,T);
	while(m--){
		int u=range(1,n+1),v=range(1,n+1);
		while(S.count(par(u,v)))u=range(1,n+1),v=range(1,n+1);
		S.insert(par(u,v));
		int s=range(1,T+1),t=range(1,T+1);
		if(s>t)swap(s,t);
		printf("%d %d %d %d\n",u,v,s,t);
	}
	return 0;
}
