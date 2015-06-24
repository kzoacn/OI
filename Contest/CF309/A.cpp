#include<bits/stdc++.h>
using namespace std;
const int mo=1e9+7;
const int maxn=1010;
typedef long long LL;
int k,c[maxn],C[maxn][maxn];
int f[maxn],sum[maxn];
LL Calc(LL n,LL m){
	return C[n+m-1][m];
}
int main(){
	C[0][0]=1;
	for(int i=1;i<maxn;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mo;
	}
	scanf("%d",&k);
	for(int i=1;i<=k;i++){
		scanf("%d",&c[i]);
		sum[i]=sum[i-1]+c[i];
	}f[1]=1;
	for(int i=2;i<=k;i++){
		f[i]=(LL)f[i-1]*Calc(sum[i-1]+1,c[i]-1)%mo;
	}cout<<f[k]<<endl;
	return 0;
}
