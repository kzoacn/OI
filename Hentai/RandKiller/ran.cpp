#include<bits/stdc++.h>
using namespace std;
int next=1;
int ran(void)
{
next = next * 1103515245 + 12345;
return (unsigned int)(next/65536) % INT_MAX;
}
int main(){
	cout<<ran()<<endl;
	cout<<rand()% 32768<<endl;
	return 0;
}
