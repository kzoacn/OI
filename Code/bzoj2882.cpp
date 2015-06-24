#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
int n;
int a[maxn];
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
	int i=0,j=1,k=0;
	while(i<n&&j<n&&k<n){
		int t=a[(i+k)%n]-a[(j+k)%n];
		if(t==0)k++;
		else if(t<0)j+=k+1,k=0;
		else i+=k+1,k=0;
		j+=i==j;
	}
	int p=min(i,j);
	for(int i=0;i<n;i++)
	printf("%d%c",a[(i+p)%n]," \n"[i+1==n]);
	return 0;
}
