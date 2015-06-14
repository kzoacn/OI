#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(0)^(long long)(new int));
	int n=10,m=10;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)printf("%d%c",rand()%n+1," \n"[i==n]);
	while(m--){
		int l=rand()%n+1,r=rand()%n+1;
		if(l>r)swap(l,r);
		printf("%d %d\n",l,r);
	}
}
