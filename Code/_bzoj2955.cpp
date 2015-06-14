#include<bits/stdc++.h>
using namespace std;
const int maxn=50010;
int n;
int a[maxn];
int sum[maxn];
int next(int i){return i+1<=n?i+1:1;}
int dis(int x,int y){
	if(x>y)swap(x,y);
	return min(sum[y]-sum[x],(sum[x])+(sum[n]-sum[y]));
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),sum[i]=sum[i-1]+a[i];
	long long ans=0;
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)
	ans=max(ans,(long long)dis(i,j));
	cout<<ans<<endl;
	return 0;
}
