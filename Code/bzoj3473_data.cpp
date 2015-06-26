#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int len=3;
string rnd(int l){
	string s;while(l--)s.push_back(rand()%3+'a');
	return s;
}
int main(){
	srand(time(0)^getpid());
	int n=2,k=rand()%len+1;
	printf("%d %d\n",n,k);
	while(n--)cout<<rnd(rand()%len+1)<<endl;
	return 0;
}
