#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int main(){
	srand(time(0)^getpid());
	int n=rand()%50+3;
	printf("%d\n",n);
	return 0;
}
