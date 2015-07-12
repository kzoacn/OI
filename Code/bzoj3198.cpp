#include<bits/stdc++.h>
using namespace std;
const int mo=1e6+3;
const int maxn=1e5+5;
typedef long long LL;
typedef unsigned long long UL;
int a[maxn][6];
int n,k;
LL cnt[7];
struct hashtab{
	static const int mo=1e6+3;
	UL a[mo];
	int b[mo];
	int vis[mo];
	int T;
	void cl(){T++;}
	int& operator[](pair<int,UL> x){
		int y=x.first;
		while(vis[y]==T&&a[y]!=x.second)y++;		
		if(vis[y]!=T){
			vis[y]=T;a[y]=x.second;b[y]=0;
			return b[y];
		}else return b[y];		
	}
}ht;
LL C(LL n,LL m){
	LL ans=1;
	for(int i=1;i<=n;i++)ans*=i;
	for(int i=1;i<=m;i++)ans/=i;
	for(int i=1;i<=n-m;i++)ans/=i;
	return ans;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	for(int j=0;j<6;j++)
	scanf("%d",&a[i][j]);
	for(int S=0;S<(1<<6);S++)if(__builtin_popcount(S)>=k){
		int cot=__builtin_popcount(S);
		ht.cl();
		for(int i=1;i<=n;i++){
			int H1=0;UL H2=0;
			for(int j=0;j<6;j++)if(S>>j&1)
				H1=(H1*13131LL+a[i][j])%mo,
				H2=(H2*233LL+a[i][j]);
			cnt[cot]+=ht[make_pair(H1,H2)];
			ht[make_pair(H1,H2)]++;
		}
	}
	LL ans=0;
	for(int i=k;i<=6;i++)
		ans+=((i-k)%2?-1:1)*cnt[i]*C(i,k);
	cout<<ans<<endl;
	return 0;
}
