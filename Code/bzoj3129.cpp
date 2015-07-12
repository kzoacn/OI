#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL inv[int(1e5)],frac[int(1e5)];
int T;
LL n,n1,n2,M,p;
LL a[17];
LL C(LL n,LL m){
	if(n<m)return 0;
	return frac[n]*inv[m]%p*inv[n-m]%p;
}
void sol(){
	cin>>n>>n1>>n2>>M;
	for(int i=0;i<n1;i++)
		cin>>a[i];
	for(int i=1;i<=n2;i++){
		LL x;cin>>x;
		M=M-x+1;
	}
	LL ans=0;
	for(int i=0;i<(1<<n1);i++){
		LL m=M;int cnt=0;
		for(int j=0;j<n1;j++)if(i>>j&1)
			m-=a[j],cnt++;				
		if(cnt&1)ans=(ans-C(m-1,n-1)+p)%p;
		else ans=(ans+C(m-1,n-1))%p;
	}
	cout<<(ans%p+p)%p<<endl;
}
int main(){
	cin>>T>>p;inv[1]=frac[1]=frac[0]=1;
	for(int i=2;i<p;i++)
	inv[i]=(p-p/i)*inv[p%i]%p,frac[i]=frac[i-1]*i%p;
	for(int i=2;i<p;i++)inv[i]=(LL)inv[i]*inv[i-1]%p;
	while(T--)sol();
	return 0;
}
