#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100000
using namespace std;
char str[100];
int main()
{
	for(int i=1;i<=10;++i)
	{
		sprintf(str,"tree < tree%d.in > tree%d.out",i,i);
		system(str);
	}
	return 0;
}
