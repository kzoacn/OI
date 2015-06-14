#include<bits/stdc++.h>
using namespace std;
int main(){
	int n=4,m=7;
	printf("%d %d\n",n,m);
	while(m--)printf("%d %d\n",rand()%n+1,rand()%n+1);
	return 0;
}
