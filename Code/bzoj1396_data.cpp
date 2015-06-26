#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int main(){
	srand(time(0)^getpid());
	int n=1000;
	while(n--)putchar(rand()%8+'a');
	puts("");
	return 0;
}
