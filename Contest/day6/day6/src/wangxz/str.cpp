#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;
int n;
bool vis[2000000];
LL k;
inline int rev(int s){
	int res=0;
	for(int i(0);i<n;i++)
		res|=((s>>i&1)<<(n-i-1));
	return res;
}
int main(){
	freopen("str.in","r",stdin);
	freopen("str.out","w",stdout);
	cin>>n>>k;
	int all((1<<n)-1);LL now=0;
	for(int s(1);s<all;s++){
		if(!vis[s^all]&&!vis[rev(s)]&&!vis[rev(s)^all])now++;
		if(now==k){
			for(int i(n-1);i>=0;i--)
				putchar((s>>i&1)?'1':'0');
			puts("");
			return 0;
		}
		vis[s]=1;
	}
	puts("-1");
	return 0;
}
