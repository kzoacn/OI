#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int n=100;
int main(){
	srand(time(0)^getpid());
	int d=rand()%15+1;
	printf("%d %d\n",n,d);
	for(int i=1;i<=n;i++)printf("%d %d\n",rand()%20,rand()%20);
	return 0;
}

