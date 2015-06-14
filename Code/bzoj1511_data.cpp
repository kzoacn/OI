#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
int main(){
	Lrand R;
	int n=R.range(4,7);printf("%d\n",n);
	while(n--)putchar(R.range('a','d'));
	puts("");return 0;
}
