#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MOD(10007);
const int N(1001);
int n,lm[N][N],rm[N][N],lu[N][N],rd[N][N],rdh[N],rdl[N],luh[N],lul[N];
bool mp[N][N];
inline bool get(){
	char c=0;
	for(;c!='C'&&c!='B';c=getchar());
	return c=='C';
}
inline int check(int x){
	if(x>=MOD)x%=MOD;
	if(x<0)x=(x%MOD+MOD)%MOD;
	return x;
}
int main(){
	freopen("rect.in","r",stdin);
//	freopen("rect.out","w",stdout);
	scanf("%d",&n);
	for(int i(1);i<=n;i++)
		for(int j(1);j<=n;j++)
			mp[i][j]=get();
	for(int i(1);i<=n;i++){
		for(int j(1);j<=n;j++)
			lm[i][j]=mp[i][j]?lm[i][j-1]+1:0;
		for(int j(n);j>=1;j--)
			rm[i][j]=mp[i][j]?rm[i][j+1]+1:0;
	}
	//lu
	for(int i(1);i<=n;i++)
		for(int j(1);j<=n;j++)
			if(mp[i][j]){
				int mn=n;
				for(int k(1);k<=n-i+1;k++){
					int x=i+k-1;
					mn=rm[x][j]<mn?rm[x][j]:mn;
					lu[i][j]=check(lu[i][j]+mn);
				}
				lu[i][j]=check(lu[i][j]-1);
			}
	//rd
	for(int i(1);i<=n;i++)
		for(int j(1);j<=n;j++)
			if(mp[i][j]){
				int mn=n;
				for(int k(1);k<=i;k++){
					int x=i-k+1;
					mn=lm[x][j]<mn?lm[x][j]:mn;
					rd[i][j]=check(rd[i][j]+mn);
				}
				rd[i][j]=check(rd[i][j]-1);
			}
	for(int i(1);i<=n;i++)
		for(int j(1);j<=n;j++)
			if(mp[i][j]){
				rdh[i]=check(rdh[i]+rd[i][j]);
				rdl[j]=check(rdl[j]+rd[i][j]);
				luh[i]=check(luh[i]+lu[i][j]);
				lul[j]=check(lul[j]+lu[i][j]);
			}
	for(int i(n);i>=1;i--)
		luh[i]=check(luh[i]+luh[i+1]),lul[i]=check(lul[i]+lul[i+1]);
	for(int i(1);i<=n;i++)
		for(int j(1);j<=n;j++)
			rd[i][j]=check(rd[i][j]+rd[i-1][j]+rd[i][j-1]-rd[i-1][j-1]);
	int ans=0;
	for(int i(1);i<=n;i++)
		ans=check(ans+rdh[i]*luh[i+1]);
	for(int i(1);i<=n;i++)
		ans=check(ans+rdl[i]*lul[i+1]);
	for(int i(1);i<=n;i++)
		for(int j(1);j<=n;j++)
			if(mp[i][j]){
				int ou=check(rd[i-1][n]+rd[n][j-1]-rd[i-1][j-1]);
				ans=check(ans+lu[i][j]*ou);
			}
	printf("%d\n",ans);
	return 0;
}
