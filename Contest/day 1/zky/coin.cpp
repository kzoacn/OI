#include<cstring>
#include<cctype>
#include<cstdio>
#include<climits>
#include<algorithm>
#include<iostream>
using namespace std;
const int maxn=1e5+5;
typedef long long LL;
int in(){
	int r=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:1,c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r*f;
}
LL dp[2001][2001];
int n,a[2001];
LL mx[2001];
namespace cheat{
	LL sum[maxn],ssum[maxn];
	struct node{
		int mn;
		int l,r;
		void rz();
	}t[maxn*2];
	int tot=0;
	void up(int &x,int y){
		if(!x||a[x]<a[y])x=y;
	}
	void node::rz(){
		up(mn,t[l].mn);
		up(mn,t[r].mn);
	}
	int build(int l,int r){
		int x=++tot;
		if(l==r){
			t[x].mn=l;
			return x;
		}
		t[x].l=build(l,(l+r)/2);
		t[x].r=build((l+r)/2+1,r);
		t[x].rz();return x;
	}
	int Qmin(int x,int l,int r,int l0,int r0){
		if(l0<=l&&r0>=r)return t[x].mn;
		int mid=(l+r)/2;
		int ans=0;
		if(l0<=mid)up(ans,Qmin(t[x].l,l,mid,l0,r0));
		if(r0>mid)up(ans,Qmin(t[x].r,mid+1,r,l0,r0));
		return ans;
	}
	int Minn(int l,int r){	
		return Qmin(1,1,n,l,r);
	}
	#define Ssum(l,r) (ssum[r]-ssum[l-1])
	LL calc(int l,int r){		
		LL ans=0;
		ans+=sum[r]-sum[l-1];
		LL len=r-l+1;
		ans+=sum[r]*len-Ssum(l-1,r-1);
		return ans;		
	}
	LL solve(int l,int r){		
		LL ans=calc(l,r);		
		int p=Minn(l,r);
		if(p==l)return ans;
		ans=max(ans,solve(l,p-1)+solve(p,r));
		return ans;
	}
	void sol(){
		build(1,n);
		
		for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
		for(int i=1;i<=n;i++)ssum[i]=ssum[i-1]+sum[i];
		LL ans=solve(2,n)+a[1];
		cout<<ans<<endl;		
	}
}
int main(){
	freopen("coin.in","r",stdin);
	freopen("coin.out","w",stdout);
	n=in();
	for(int i=1;i<=n;i++)a[i]=in();
	if(n>2000){
		cheat::sol();
		return 0;
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		dp[i][j]=-(1LL<<62);
	LL ans=-(1LL<<62);
	dp[1][1]=a[1];
	dp[2][2]=a[1]+a[2]*2;
	mx[1]=mx[2]=dp[2][2];
	if(n==1)return cout<<dp[1][1]<<endl,0;
	if(n==2)return cout<<dp[2][2]<<endl,0;
	for(int i=3;i<=n;i++){
		for(int j=2;j<=i;j++){
			dp[i][j]=mx[j-1];
			dp[i][j]+=(LL)a[i]*j;
			if(i==n)ans=max(ans,dp[i][j]);
		}
		mx[i+1]=-(1LL<<62);
		for(int j=i;j>=1;j--)
			mx[j]=max(mx[j+1],dp[i][j]);
	}
	
	cout<<ans<<endl;
	return 0;
}
