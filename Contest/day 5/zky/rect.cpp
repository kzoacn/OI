#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=1010;
int n;
char s[maxn];
int sum[maxn][maxn];
#define Sum(xl,xr,yl,yr) (sum[xr][yr]-sum[xr][yl-1]-sum[xl-1][yr]+sum[xl-1][yl-1])
int find(int xl,int xr,int yl,int yr){
	int ans=0;
	for(int i=1;i<=n;i++)
	for(int j=i;j<=n;j++)
	for(int k=1;k<=n;k++)
	for(int l=k;l<=n;l++){
		if(j<xl||i>xr||l<yl||k>yr){	
			if(Sum(i,j,k,l)==(j-i+1)*(l-k+1)&&(j-i+1)*(l-k+1)>=2)
				ans++;
			else if((j-i+1)*(l-k+1)>=2)
				break;
		}
	}
	return ans;
}
int main(){
	freopen("rect.in","r",stdin);
	freopen("rect.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=n;j++)
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+(s[j]=='C');
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	for(int j=i;j<=n;j++)
	for(int k=1;k<=n;k++)
	for(int l=k;l<=n;l++)
		if(Sum(i,j,k,l)==(j-i+1)*(l-k+1)&&(j-i+1)*(l-k+1)>=2)
			ans+=find(i,j,k,l);
		else if((j-i+1)*(l-k+1)>=2)
			break;
	
	cout<<(ans/2)%10007<<endl;
	return 0;
}
