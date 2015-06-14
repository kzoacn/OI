#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
int n;
int a[maxn];
struct seg{
	int l,r;
	LL val;
	bool operator<(seg oth)const{return sum>oth.sum;}
}se[maxn];
int main(){
	n=in();int m=(n+1)>>1;
	for(int i=1;i<=n;i++)a[i]=in();
	for(int i=1;i<=m;i++)a[i+n]=a[i];
	long long sum=accumulate(a+1,a+1+m);
	
	return 0;
}
