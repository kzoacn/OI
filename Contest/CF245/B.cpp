#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1010;
LL a[maxn][maxn];
int n,m;
LL f1[maxn][maxn];
LL f2[maxn][maxn];
LL f3[maxn][maxn];
LL f4[maxn][maxn];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%I64d",&a[i][j]);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	f1[i][j]=max(f1[i-1][j],f1[i][j-1])+a[i][j];
	
	for(int i=1;i<=n;i++)
	for(int j=m;j>=1;j--)
	f2[i][j]=max(f2[i-1][j],f2[i][j+1])+a[i][j];
	
	for(int i=n;i>=1;i--)
	for(int j=m;j>=1;j--)
	f3[i][j]=max(f3[i+1][j],f3[i][j+1])+a[i][j];
	
	for(int i=n;i>=1;i--)
	for(int j=1;j<=m;j++)
	f4[i][j]=max(f4[i+1][j],f4[i][j-1])+a[i][j];
	
	LL ans=0;
    for(int i=2;i<n;i++){
        for(int j=2;j<m;j++){ 
			ans=max(ans,f1[i-1][j]+f3[i+1][j]+f4[i][j-1]+f2[i][j+1]);
        	ans=max(ans,f1[i][j-1]+f3[i][j+1]+f4[i+1][j]+f2[i-1][j]);
        }  
    }
	cout<<ans<<endl;
	return 0;
}
