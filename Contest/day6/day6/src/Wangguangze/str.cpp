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
const int N = 22;
int f[1<<N],g[1<<N],n,k,A[22];
inline void print(LL A,int n){
	for (int i=n-1;i>=0;i--)
		printf("%lld%c",A>>i&1,i?' ':'\n');
}
inline int work(){
	int ret=0;
	for (int i=0;i<n;i++)
		ret=ret<<1|A[i];
	return ret;
}
int main()
{
	freopen("str.in","r",stdin);
	freopen("str.out","w",stdout);
	n=read(); k=read();
	f[(1<<n)-1]=1;
	for (int i=1;i<(1<<n);i++){
		if (f[i]) continue;
		k--;
	//	print(i,n);
		if (k==0){
			print(i,n);
			return 0;
		}
		for (int j=0;j<n;j++) A[j]=i>>j&1;
		f[work()]=1; 
		for (int j=0;j<n;j++) A[j]^=1;
		f[work()]=1;
		reverse(A,A+n);
		f[work()]=1;
		for (int j=0;j<n;j++) A[j]^=1;
		f[work()]=1;
	}
	printf("-1\n");
	return 0;
}
	
