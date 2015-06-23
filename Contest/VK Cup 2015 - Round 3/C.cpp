#include<bits/stdc++.h>
using namespace std;
const int maxn=1001;
int f[maxn][maxn],n;
typedef long long LL;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&f[1][i]);
	for(int i=1;i<n*5;i++)
	for(int j=1;j<=n;j++)
	f[i+1][j]=f[1][f[i][j]];
	long long LCM=1,mn=0;
	for(int i=1;i<=n;i++){
        int t1=1;
        while(f[t1][i]!=f[t1*2][i])t1++;
        int t2=t1+1;
        while(f[t2][i]!=f[t2*2][i])t2++;
        mn=max(mn,(LL)t1);
        LCM=LCM/__gcd(LCM,(LL)t2-t1)*(t2-t1);
	}
	long long l=LCM;
	while(LCM<mn)LCM+=l;
	cout<<LCM<<endl;
	return 0;
}
