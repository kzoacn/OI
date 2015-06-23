#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,m;
int calc(int len,int h1,int h2){
	if(h1>h2)swap(h1,h2);
	int x=(len+h2-h1)/2+h1;
 	int y=0;
	return max(x,y);
}
int h[maxn],d[maxn];
int ans=-1;
int main(){
	scanf("%d%d",&n,&m);
	scanf("%d%d",&d[1],&h[1]);
	if(m==1){
		cout<<max(d[1]-1,n-d[1])+h[1]<<endl;
		return 0;
	}
	for(int i=2;i<=m;i++){
		scanf("%d%d",&d[i],&h[i]);
		if(d[i]-d[i-1]<abs(h[i]-h[i-1]))return puts("IMPOSSIBLE"),0;
		ans=max(ans,calc(d[i]-d[i-1],h[i-1],h[i]));
	}
	ans=max(ans,d[1]-1+h[1]);
	ans=max(ans,n-d[m]+h[m]);
	cout<<ans<<endl;
	return 0;
}
