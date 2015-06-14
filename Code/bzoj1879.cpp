#include<bits/stdc++.h>
using namespace std;
const int MOD=1000003;
int n,k;
string s[16];
int f[51][1<<16];
int can[51][26];
void solve(){
	memset(f,0,sizeof f);
	memset(can,0,sizeof can);
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++)cin>>s[i];
	int len=s[0].length();
	for(int i=0;i<len;i++)
	for(int j=0;j<n;j++)
	for(int k=0;k<26;k++)
	if(s[j][i]=='?'||s[j][i]==k+'a')
	can[i][k]|=1<<j;
	f[0][(1<<n)-1]=1;
	for(int i=0;i<len;i++){
		for(int j=0;j<(1<<n);j++)if(f[i][j]){
			for(int k=0;k<26;k++){
				f[i+1][j&can[i][k]]+=f[i][j];
				if(f[i+1][j&can[i][k]]>=MOD)
				f[i+1][j&can[i][k]]%=MOD;
			}
		}
	}int ans=0;
	for(int i=0;i<(1<<n);i++)if(__builtin_popcount(i)==k)ans=(f[len][i]+ans)%MOD;
	cout<<ans<<endl;
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
