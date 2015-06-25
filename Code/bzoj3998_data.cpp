#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int main(){
	srand(time(0)^getpid());
	int n=800;
	while(n--)putchar(rand()%26+'a');puts("");
	printf("%d %d\n",rand()%2,rand()%900+1);
	return 0;
}
