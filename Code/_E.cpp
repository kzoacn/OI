#include<bits/stdc++.h>
using namespace std;
const int mo=1e9+7;
typedef unsigned long long uL;
typedef long long LL;
int n,q;
char s[5001];
uL hash[5001],hash_l[5001];
int anss[5001];
int fac[5001],inv[5001];
pair<uL,int> has[5000*5000+2];
int hash2[5001],hash_l2[5001];
LL C(int n,int m){
	return (LL)fac[n]*inv[m]%mo*inv[n-m]%mo;
}
pair<uL,int> get(int l,int r){
	return make_pair(hash[r]-hash[l-1]*hash_l[r-l+1],(hash2[r]-hash2[l-1]*hash_l2[r-l+1]%10007+10007)%10007);
}
void sol(){
	memset(anss,0,sizeof anss);
	int m=0;
	scanf("%d%d",&n,&q);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)hash[i]=hash[i-1]*31+s[i];
	for(int i=1;i<=n;i++)hash2[i]=(hash2[i-1]*233+s[i])%10007;
	for(int i=1;i<=n;i++)
	for(int j=i;j<=n;j++)has[++m]=get(i,j);
	sort(has+1,has+1+m);
	int j=1,cnt=0;pair<uL,int> cur=has[1];
	for(;j<=m+1;j++){
		if(j!=m+1&&has[j]==cur)cnt++;
		else{
			for(int k=1;k<=cnt;k++)anss[k]=(anss[k]+C(cnt,k))%mo;
			cnt=1;cur=has[j];
		}
	}
	while(q--){
		int k;scanf("%d",&k);
		if(k>n)puts("0");
		else printf("%d\n",anss[k]);
	}memset(&has[1],0,sizeof(pair<uL,int>)*m);
}
int main(){
	freopen("E.in","r",stdin);
	fac[0]=inv[0]=inv[1]=hash_l[0]=hash_l2[0]=1;
	for(int i=1;i<=5000;i++)hash_l[i]=hash_l[i-1]*31;
	for(int i=1;i<=5000;i++)hash_l2[i]=hash_l2[i-1]*233%10007;
	for(int i=1;i<=5000;i++)fac[i]=(LL)fac[i-1]*i%mo;
	for(int i=2;i<=5000;i++)inv[i]=(LL)(mo-mo/i)*inv[mo%i]%mo;
	for(int i=2;i<=5000;i++)inv[i]=(LL)inv[i]*inv[i-1]%mo;
	int T;scanf("%d",&T);
	while(T--)sol();
	return 0;
}
