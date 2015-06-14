#include<bits/stdc++.h>
using namespace std;
int n,m,red[1001];
int main(){
	scanf("%d%d",&n,&m);
	while(m--){
		int u,v;scanf("%d%d",&u,&v);
		red[u]++;red[v]++;
	}long long ans=0;
	for(int i=1;i<=n;i++){
		long long r=red[i],b=n-red[i]-1;
		ans+=r*b;
	}cout<< (long long)n*(n-1)*(n-2)/6-ans/2 <<endl;
	return 0;
}
