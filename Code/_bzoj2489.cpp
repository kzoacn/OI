#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int n;
int a[32];
int calc(){
	int sum[32];sum[0]=0;
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
	int ans=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=i;j++)
	ans=max(abs(sum[i]-sum[j-1]),ans);
	return ans;
}
LL calc(int n){
	::n=n;
	long long ans=0;
	for(int i=0;i<(1<<n);i++){
		for(int j=0;j<n;j++){
			a[j+1]=(i>>j&1)?1:-1;
		}ans+=calc();
	}return ans;
}
LL b[32],c[32],d[32];
int main(){
	for(int i=1;i<=15;i++){
		printf("%d:%lld  %.6lf\n",i,b[i]=calc(i),calc(i)/double(1<<i));
	}
	for(int i=1;i<=15;i++)printf("%lld%c",c[i]=b[i]-b[i-1]," \n"[i==15]);
	for(int i=1;i<=15;i++)printf("%lld%c",d[i]=c[i]-c[i-1]," \n"[i==15]);
	for(int i=1;i<=15;i++)printf("%lld%c",d[i]-d[i-1]," \n"[i==15]);
	return 0;
}
