#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1<<11;
LL L,R;
LL ans=0;
LL a[maxn],b[maxn];
void dfs1(int x,LL y){
	if(y>R)return;
	if(x>0)a[++a[0]]=y;
	dfs1(x+1,y*10+2);
	dfs1(x+1,y*10+9);
}
LL lcm(LL a,LL b){return a*b/__gcd(a,b);}
double dcm(LL a,LL b){return double(a)*b/__gcd(a,b);}
void dfs(int x,LL l,int cur){
	if(x>b[0]){
		if(cur)ans+=(R/l-(L-1)/l)*(cur%2?1:-1);
		return;
	}
	dfs(x+1,l,cur);
	if(dcm(l,b[x])<=R&&lcm(l,b[x])<=R)
		dfs(x+1,lcm(l,b[x]),cur+1);
}
int main(){
	cin>>L>>R;
	dfs1(0,0);
	sort(a+1,a+1+a[0]);
	static int vis[maxn];
	for(int i=1;i<=a[0];i++)if(!vis[i]){
		b[++b[0]]=a[i];
		for(int j=i+1;j<=a[0];j++)if(a[j]%a[i]==0)
			vis[j]=1;
	}reverse(b+1,b+1+b[0]);
	dfs(1,1,0);
	cout<<ans<<endl;
	return 0;
}
