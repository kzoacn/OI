#include<bits/stdc++.h>
using namespace std;
double f[102][1<<15];
int n,k,sc[16],pre[16];
int main(){
	scanf("%d%d",&k,&n);
	for(int i=0;i<n;i++){
		scanf("%d",&sc[i]);int x;
		while(scanf("%d",&x),x)pre[i]|=1<<(x-1);
	}
	for(;k;k--){
		for(int S=0;S<(1<<n);S++){
			for(int j=0;j<n;j++){
				if((S&pre[j])==pre[j])
					f[k][S]+=max(f[k+1][S|(1<<j)]+sc[j],f[k+1][S])/n;
				else f[k][S]+=f[k+1][S]/n;
			}
		}
	}printf("%.6lf\n",f[1][0]);
	return 0;
}
