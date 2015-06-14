#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(0)^(long long)(new int));
	int n=rand()%9+1;
	printf("%d %d\n",n,rand()%(n*n));
	return 0;
}
