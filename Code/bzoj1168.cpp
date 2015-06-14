#include<bits/stdc++.h>
using namespace std;
int f[1<<20],g[1<<20],n,a[20],b[20];
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		f[1<<i]=a[i];
	}
	for(int i=0;i<n;i++){
		cin>>b[i];
		g[1<<i]=b[i];
	}
	for(int i=0;i<(1<<n);i++)if((i&-i)!=i){
		f[i]=f[i^(i&-i)]+f[(i&-i)];
		g[i]=g[i^(i&-i)]+g[(i&-i)];
	}
	int ansx=2e9,ansy=2e9;
	for(int i=1;i<(1<<n);i++){
		int x=f[i],y=g[i^((1<<n)-1)];
		if(!x||!y)continue;
		if(x+y<(long long)ansx+ansy)ansx=x,ansy=y;
		if(x<ansx&&y==ansy)ansx=x,ansy=y;
	}cout<<ansx<<" "<<ansy<<endl;
	return 0;
}
