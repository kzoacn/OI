#include<bits/stdc++.h>
using namespace std;
double range(int l,int r){
	l*=10,r*=10;
	return (rand()%(r-l)+l)/10.0;
}
int main(){
	srand(time(0));
	int n=2;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	printf("%.1lf%c",range(0,4)," \n"[j==n]);
	return 0;
}
