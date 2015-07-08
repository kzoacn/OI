#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
int T,F;
int SG[maxn],vis[maxn];
int sg(int n){
	if(n<F)return 0;
	if(vis[n])return SG[n];
	vis[n]=1;
	
}
int main(){
	scanf("%d%d",&T,&F);
	while(T--){
		int n;scanf("%d",&n);
		int ans=0;
		for(int i=1;i<=n;i++){
			int x;scanf("%d",&x);
			ans^=sg(x);
		}puts(ans?"1":"0");
	}
	return 0;
}
