#include<bits/stdc++.h>
using namespace std;
int f(int h){
    h ^= (h >> 20) ^ (h >> 12);
    return h ^ (h >> 7) ^ (h >> 4);
}
int main(){
	unordered_set<int>ht;
	set<int>S;
	for(int i=1;i<=25;i++)	{
		cout<<f(i)<<",";
	}
	return 0;
}
