#include<bits/stdc++.h>
using namespace std;
const int maxn=5e4+4;
int n,m,T;
int u[maxn],d[maxn],p[maxn],notp[maxn];
int main(){
	scanf("%d",&T);
	u[1]=1;
	for(int i=1;i<maxn;i++)d[i]++;
	for(int i=2;i<maxn;i++){
		if(!notp[i]){u[i]=-1;p[++p[0]]=i;}
		for(int j=1;j<=p[0]&i*p[j]<maxn;j++){
			notp[i*p[j]]=1;
			if(i%p[j]==0){
				u[i*p[j]]=0;
				break;
			}else u[i*p[j]]=-u[i];
		}for(int j=i;j<maxn;j+=i)d[j]++;
	}for(int i=2;i<maxn;i++)u[i]+=u[i-1],d[i]+=d[i-1];
	while(T--){
		int n,m;scanf("%d%d",&n,&m);
		if(n>m)swap(n,m);
		int j;long long ans=0;
		for(int i=1;i<=n;i=j+1){
			j=min(n/(n/i),m/(m/i));
			ans+=(long long)(u[j]-u[i-1])*d[n/i]*d[m/i];
		}printf("%lld\n",ans);
	}
	return 0;
}
