#include<bits/stdc++.h>
#include<process.h>
using namespace std;
int main(){
	srand(time(0)^_getpid());
	int T=3;
	printf("%d\n",T);
	while(T--){
		int n=rand()%100000+2;printf("%d\n",n);
		for(int i=1;i<=n;i++)printf("%d%c",rand()%n+1," \n"[i==n]);
	}
	return 0;
}
