//coder : davidwang
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cerrno>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <iostream>
using namespace std;
#define LL long long
#define X first
#define Y second
inline int read()
{
	int ret=0,f=1; char ch;
	for (ch=getchar();ch<'0' || ch>'9';ch=getchar())
		if (ch=='-') f=-f;
	for (;'0'<=ch && ch<='9';ch=getchar())
		ret=ret*10+ch-'0';
	return ret*f;
}
int n;
LL k;
int f[26][2][2];
//满足一个>=x 并且01饭装之后>=x的数字，flag 表示01反转之后是否必须严格大于
inline int Dpsolve(int x,int n,int flag){
	memset(f,0,sizeof(f));
	f[0][0][0]=1;
	for (int i=0;i<n;i++){
		int v=x>>(n-i-1)&1;
		for (int a1=0;a1<2;a1++)
			for (int a2=0;a2<2;a2++){
				if (f[i][a1][a2]==0) continue;
				
				for (int k=0;k<2;k++){
					if (a1==0 && k<v) continue;
					if (a2==0 && k && v) continue;
					f[i+1][a1|(k>v)][a2|(k==0 && v==0)]+=f[i][a1][a2];
				}
				/*
				if (a1==1 || v==0) f[i+1][a1][a2|(v==0)]+=f[i][a1][a2];
				if (a2==1 || v==0) f[i+1][1][a2]+=f[i][a1][a2];*/
			}
	}
	int ans=f[n][1][1]+f[n][0][1];
	if (flag==0) ans+=f[n][1][0]+f[n][0][0];
	return ans;
}
int A[40],B[40];
inline int ok(int a,int b,int n,int flag){
	if (flag) flag&=a&1,a>>=1;
	for (int i=0;i<n;i++)
		A[i]=a>>(n-i-1)&1,B[i]=b>>i&1;
	//	reverse(A,A+n);
	for (int i=0;i<n;i++){
		if (A[i]>B[i]) return 0;
		if (B[i]>A[i]) break;
	}
	int i;
	for (i=0;i<n;i++){
		if (A[i]>(B[i]^1)) return 0;
		if ((B[i]^1)>A[i]) break;
	}
	if (i==n && flag) return 0;
	return 1;
}
//n是偶数
LL work0(int n,LL k)
{
	k++;
	int i,limit=1<<(n/2-1);
	for (i=0;i<limit;i++){
		int now=(1<<n/2)-2*i;
		if (now<k){
			k-=now;
			continue;
		}
		int flag=0;
		if (k<now/2){
			for (int j=0;j<(1<<n/2);j++){
				if (ok(i,j,n/2,0)) k--/*,printf("%d\n",j)*/;
				if (k==0) return (LL)(i)<<(n/2)|(j+k);
			}
			
		}else{
			k=now-k+1;
			for (int j=(1<<n/2)-1;;j--){
				if (ok(i,j,n/2,0)) k--;
				if (k==0) return (LL)i<<(n/2)|(j+k);
			}
		}
	}
	return -1;
}
LL work1(int n,LL k){
	k++;
	int i,limit=1<<(n/2);
	for (int i=0;i<=limit;i++){
		if (i>>n/2&1) return -1;
	//	int now=Dpsolve(i/2,n/2,i&1);
		int now=(1<<(n/2))-i;
	//	printf("%d\n",now);
		if (now<k){
			k-=now;
			continue;
		}
		if (k<now/2){
			for (int j=0;j<(1<<n/2);j++){
				if (ok(i,j,n/2,1)) k--;
				if (!k) return (LL)(i)<<(n/2)|(j+k);
			}
		}else{
			k=now-k+1;
			for (int j=(1<<n/2)-1;j>=0;j--){
				if (ok(i,j,n/2,1)) k--;
				if (!k) return (LL)(i)<<(n/2)|j;
			}
		}
	}
	return -1;
}
inline void print(LL A,int n){
	if (A==-1){ puts("-1"); return;} 
	for (int i=n-1;i>=0;i--)
		printf("%lld",A>>i&1);
	puts("");
}
int main()
{
	freopen("str.in","r",stdin);
	freopen("str.out","w",stdout);
	scanf("%d%I64d",&n,&k);
	print(n&1?work1(n,k):work0(n,k),n);
	return 0;
}
