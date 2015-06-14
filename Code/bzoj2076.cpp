#include<bits/stdc++.h>
using namespace std;
int n;
double v[1230],f[5736397];
int w[1230],p[1230],g[5736397],notp[10001];
void solve(){
	scanf("%d",&n);
	w[0]=0;int m=0;
	for(int i=1;i<=p[0];i++)if(p[i]<=n)
		w[++w[0]]=p[i],v[w[0]]=log(p[i]);
	else break;
	m=accumulate(w+1,w+1+w[0],0);
	
}
int main(){
	int _;scanf("%d",&_);
	for(int i=2;i<=10000;i++){
		if(!notp[i])p[++p[0]]=i;
		for(int j=1;j<=p[0]&&i*p[j]<=10000;j++){
			notp[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
	while(_--)solve();
	return 0;
}
