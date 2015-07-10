#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int n=1000;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
	srand(time(0)^getpid());
	freopen("deep.in","w",stdout);
	printf("%d\n",n);
	for(int i=2;i<=n;i++)printf("%d%c",range(1,i)," \n"[i==n]);
	for(int i=1;i<=n;i++)printf("%c%c",range(0,2)?'(':')'," \n"[i==n]);
	return 0;
}
