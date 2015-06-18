#include<bits/stdc++.h>
using namespace std;
int n,m;
int in(){
	int r=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r*f;
}
int a[201][201];
int val[200*200+10];
int main(){
	n=in();m=in();
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	a[i][j]=in,val[++val[0]]=a[i][j];
	sort(val+1,val+1+val[0]);
	val[0]=unique(val+1,val+1+val[0])-val-1;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	a[i][j]=lower_bound(val+1,val+1+val[0],a[i][j])-val;
	
	return 0;
}
