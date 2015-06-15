#include<bits/stdc++.h>
using namespace std;
int n;
struct pack:public pair<int,int>{
	int &f(){return first;}
	int &s(){return second;}
};
void solve(int l,int r){
	int n=(r-l+1)/2-1;
	if(n==4){
		printf("%d to %d\n",r-2,l);
		printf("%d to %d\n",l+4,r-2);
		printf("%d to %d\n",l+1,l+4);
		printf("%d to %d\n",r-1,l+1);
	}else if(n==5){
		printf("%d to %d\n",r-2,l);
		printf("%d to %d\n",l+4,r-2);
		printf("%d to %d\n",r-4,l+4);
		printf("%d to %d\n",l+1,r-4);
		printf("%d to %d\n",r-1,l+1);
	}else if(n==6){
		printf("%d to %d\n",r-2,l);
		printf("%d to %d\n",r-5,r-2);
		printf("%d to %d\n",l+3,r-5);
		printf("%d to %d\n",r-6,l+3);
		printf("%d to %d\n",l+1,r-6);
		printf("%d to %d\n",r-1,l+1);
	}else if(n==7){
		printf("%d to %d\n",r-2,l);
		printf("%d to %d\n",l+6,r-2);
		printf("%d to %d\n",l+9,l+6);
		printf("%d to %d\n",l+4,l+9);
		printf("%d to %d\n",r-5,l+4);
		printf("%d to %d\n",l+1,r-5);
		printf("%d to %d\n",r-1,l+1);
	}else{
		printf("%d to %d\n",r-2,l);
		printf("%d to %d\n",l+4,r-2);
		solve(l+4,r-4);
		printf("%d to %d\n",l+1,r-5);
		printf("%d to %d\n",r-1,l+1);
	}
}
int main(){
	cin>>n;
	if(n==3){
		puts("2 to -1");
		puts("5 to 2");
		puts("3 to -3");
	}else
		solve(-1,n*2);
	return 0;
}
