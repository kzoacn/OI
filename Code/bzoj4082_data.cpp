#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int main(){
	srand(time(0)^getpid());
	int n=100,m=rand()%n+80;
	printf("%d %d\n",n,m);
	while(m--)printf("%d %d\n",rand()%n+1,rand()%n+1);
	return 0;
}
