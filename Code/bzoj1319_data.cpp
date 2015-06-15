#include<bits/stdc++.h>
using namespace std;
int p=1e9+7,k,a;
int main(){
	srand(time(0)^(long long)(new int));
	k=rand()%(p-3)+2;a=rand()%p;
	printf("%d %d %d\n",p,k,a);
	return 0;
}
