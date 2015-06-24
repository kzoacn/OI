#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
typedef pair<int,int> ppar;
set<ppar>S;
ppar par(int u,int v){return ppar(min(u,v),max(u,v));}
int main(){
	freopen("D.in","w",stdout);
	srand(time(0)^getpid());
	int n=4e3,m=1e5,k=2000;
	printf("%d %d %d\n",n,m,k);
	for(int i=1;i<=k;i++)printf("%d%c",rand()%n+1," \n"[i==k]);
	while(m--){
		int u=rand()%n+1,v=rand()%n+1;
		while(S.count(par(u,v))||u==v)u=rand()%n+1,v=rand()%n+1;
		S.insert(par(u,v));
		printf("%d %d\n",u,v);
	}
	return 0;
}
