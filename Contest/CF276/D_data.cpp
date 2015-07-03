#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int main(){
//	freopen("D.in","w",stdout);
	srand(time(0)^getpid());
	int n=20;
	printf("%d\n",n);
	long long sum=0;
	for(int i=1;i<=n;i++)
		printf("%d%c",sum+=(rand()%40-20)," \n"[i==n]);
	return 0;
}
