#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+5;;
int n;
int a[maxn],b[maxn],c[maxn];
int lb[maxn],mx;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		a[x]=1;mx=max(mx,x);
	}
	for(int i=1;i<=mx;i++)if(a[i])
		for(int j=i+i;j<=mx*2;j+=i){
			b[j-1]=max(b[j-1],i-1);
		}
	
	int cur=0;
	for(int i=mx*2;i>=1;i--){
		cur=max(cur,b[i]);
		c[i]=cur--;
	}
	
	
	int ans=0;
	for(int i=1;i<=mx;i++)if(a[i])
		ans=max(ans,c[i]);
	cout<<ans<<endl;	
	return 0;
}
