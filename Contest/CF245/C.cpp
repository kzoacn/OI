#include<bits/stdc++.h>
using namespace std;
int n;
int a[233],vis[223],fa[233],son[233],b[233];
bool check(){
	for(int i=1;i<n;i++)
	if(son[i]<2&&b[i]!=1)
		return false;
	return true;
}
int T=1e7;
bool dfs(int x){
	if(clock()/double(CLOCKS_PER_SEC)>0.8){
		puts("NO");
		exit(0);
	}
	if(x==n){
		return check();
	}
	for(int i=x+1;i<=n;i++)
	if(b[i]-a[x]>=1){
			if(b[i]-a[x]==1&&son[i]==0)continue;
			b[i]-=a[x];
			son[i]++;
			if(dfs(x+1))
				return true;
			son[i]--;
			b[i]+=a[x];
		}
	return false;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];b[i]=a[i];
		if(a[i]==2)return puts("NO"),0;
//		a[i]--;
	}
	sort(a+1,a+1+n);
	sort(b+1,b+1+n);
	puts(dfs(1)?"YES":"NO");
	return 0;
}
