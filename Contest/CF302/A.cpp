#include<bits/stdc++.h>
using namespace std;
const int maxn=501;
int f[maxn][maxn];
int a[maxn],sum[maxn];
int n,m,b,mo;
void up(int &x,int y){x+=y;if(x>=mo)x-=mo;}
int main(){
	scanf("%d%d%d%d",&n,&m,&b,&mo);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	f[0][0]=1;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	for(int k=a[i];k<=b;k++)
	f[j][k]=(f[j][k]+f[j-1][k-a[i]])%mo;
	int ans=0;
	for(int i=0;i<=b;i++)up(ans,f[m][i]);
	cout<<ans<<endl;
	return 0;
}
