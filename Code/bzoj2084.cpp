#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long LL;

#define N 500010
char s1[N],s2[N];

const int base=2333;
int mi[N],f1[N],f2[N];
int git1(int l,int r){return f1[l]-(LL)f1[r+1]*mi[r-l+1];}
int git2(int l,int r){return f2[l]-(LL)f2[r+1]*mi[r-l+1];}
int main(){
	int n;scanf("%d",&n);
	scanf("%s",s1+1);register int i,j;for(i=1;i<=n;++i)s2[i]=s1[n-i+1]=='0'?'1':'0';
	//printf("%s\n%s\n",s1+1,s2+1);
	for(mi[0]=1,i=1;i<=n;++i)mi[i]=(LL)mi[i-1]*base;
	for(i=n;i>=1;--i)f1[i]=((LL)base*f1[i+1]+s1[i]);
	for(i=n;i>=1;--i)f2[i]=((LL)base*f2[i+1]+s2[i]);

	long long res=0;
	int L,R,mid;
	for(i=1;i<=n;++i){
		j=n-i+1;
		L=0,R=min(i,n-i+1);
		while(L<R){
			mid=(L+R+1)>>1;
			if(git1(i-mid+1,i+mid-1)==git2(j-mid+1,j+mid-1))L=mid;else R=mid-1;
		}res+=L;
	}
	for(i=1;i<n;++i){
		j=n-i;
		L=0,R=min(i,n-i);
		while(L<R){
			mid=(L+R+1)>>1;
			if(git1(i-mid+1,i+mid)==git2(j-mid+1,j+mid))L=mid;else R=mid-1;
		}res+=L;
	}
	printf("%lld\n",res);
	return 0;
}
