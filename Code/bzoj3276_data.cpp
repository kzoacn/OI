#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int range(int l,int r){return rand()%(r-l)+l;}
int main(){
	freopen("bzoj3276.in","w",stdout);
	srand(time(0)^getpid());
	int w=1e9;
	int n=250000;
	printf("%d %d %d %d %d\n",range(1,w),range(1,w),range(1,w),range(1,w),n);
	while(n--)	
	printf("%d %d %d %d %d\n",range(1,w),range(1,w),range(1,w),range(1,w),range(1,w),n);
	return 0;
}
