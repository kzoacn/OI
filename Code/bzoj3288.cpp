#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
int n,mod=1000000007;
int p[maxn],minp[maxn],phi[maxn];
int main(){
	cin>>n;phi[1]=1;
	for(int i=2;i<=n;i++){
		if(!minp[i]){p[++p[0]]=i;minp[i]=i;phi[i]=i-1;}
		for(int j=1;j<=p[0]&&i*p[j]<=n;j++){
			minp[i*p[j]]=p[j];
			if(i%p[j]==0){phi[i*p[j]]=phi[i]*p[j];break;}
			phi[i*p[j]]=phi[i]*(p[j]-1);
		}
	}long long ans=0;
	for(int i=1;i<=n;i++){
		ans*=phi[i];
		if(ans>=mod)ans%=mod;
	}cout<<ans<<endl;
	return 0;
}

