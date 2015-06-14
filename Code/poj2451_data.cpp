#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;
int n=1000;
int f(double x){
	if(x>5000)x-=5000;
	return sqrt(25000000.0-(double)x*x);
}
int main(){
	Lrand R;
	printf("%d\n",n);
	while(n--){
		int x=R.range(0,10000);
		int xx=R.range(x,10000);
		printf("%d %d %d %d\n",xx,f(xx),x,f(x));
	}
	return 0;
}
