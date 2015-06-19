#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL F[18][11][11];
LL f[18][11],ten[17];
valarray<LL> solve(LL n){
	if(!n){valarray<LL>tmp;tmp.resize(10);tmp[0]=1;return tmp;}
	memset(f,0,sizeof f);memset(F,0,sizeof F);
	int a[13],len=0;memset(a,0,sizeof a);
	for(LL i=1,x=n;x;i++)a[i]=x%10,x/=10,len++;
	for(int i=1;i<=len;i++)
	for(int j=i==len;j<=9;j++)
	for(int k=0;k<10;k++){
		F[i][j][k]=LL(j==k)*ten[i-1];
		for(int l=0;l<=9;l++)
		F[i][j][k]+=F[i-1][l][k];
		F[i][10][k]+=F[i][j][k];
	}

	for(int i=1;i<=len;i++)
	for(int k=0;k<=9;k++){
		for(int j=i==len;j<=a[i]-1;j++)
		f[i][k]+=F[i-1][10][k]+LL(j==k)*ten[i-1];
		f[i][k]+=f[i-1][k]+LL(a[i]==k)*(n%ten[i-1]+1);
		f[i][10]+=f[i][k];
	}
	valarray<LL>res=valarray<LL>(F[len-1][10],10)+valarray<LL>(f[len],10);
	LL sum=1;
	for(int i=1;i<len;i++)sum+=(ten[i]-ten[i-1])*i;
	sum+=(n-ten[len-1]+1)*len;
	res[0]=sum-(res.sum()-res[0]);
	res[0]--;
	return res;
}
bool cmp(valarray<LL> a,valarray<LL> b){
	for(int i=0;i<10;i++)
		if(b[i]>a[i])return false;
	return true;
}
void sol(){
	valarray<LL>tar;tar.resize(10);
	for(int i=0;i<10;i++)cin>>tar[i];
	LL l=1,r=1e16;
	while(l<r){
		LL mid=(l+r)>>1;
		valarray<LL>tmp=solve(mid);
//		for(int i=0;i<10;i++)cout<<tmp[i]<<" ";cout<<endl;
//		for(int i=0;i<10;i++)cout<<tar[i]<<" ";cout<<endl;
		if(cmp(tar,tmp))
			l=mid+1;
		else r=mid;
	}cout<<l-1<<endl;
}
int main(){
	freopen("t2.in","r",stdin);
	freopen("t2.out","w",stdout);
	ten[0]=1;for(int i=1;i<=17;i++)ten[i]=ten[i-1]*10;
	int T;cin>>T;
	while(T--)sol();
	return 0;
}
