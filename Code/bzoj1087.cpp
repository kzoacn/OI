#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
vector<int>opt[1<<9];
LL f[10][100][1<<9];
int n,k,cnt[1<<9];
int main(){
	cin>>n>>k;
	for(int i=0;i<(1<<n);i++)cnt[i]=__builtin_popcount(i);
	for(int i=0;i<(1<<n);i++){
		if(((i<<1)&i)|((i>>1)&i))continue;
		f[1][cnt[i]][i]=1;
		for(int j=0;j<(1<<n);j++){
			if(((j<<1)&j)|((j>>1)&j))continue;
			if(((i<<1)&j)|((i>>1)&j)|(i&j))continue;
			opt[i].push_back(j);
		}
	}for(int i=2;i<=n;i++)
	for(int S=0;S<(1<<n);S++)
	for(int j=0;j<=k;j++)
	for(int l=0;l<opt[S].size();l++){
		int SS=opt[S][l];
		if(j<cnt[S])continue;
		f[i][j][S]+=f[i-1][j-cnt[S]][SS];
	}cout<<accumulate(f[n][k],f[n][k]+(1<<n),0LL);
	return 0;
}
