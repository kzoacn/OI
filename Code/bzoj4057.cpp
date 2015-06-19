#include<bits/stdc++.h>
using namespace std;
int n;
int f[1<<20];
int d[20][20];
int sum[20];
void sol(){
	//memset(f,0,sizeof f);
	scanf("%d",&n);
	for(int i=0;i<(1<<n);i++)f[i]=0;
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
		scanf("%d",&d[i][j]);
	f[0]=1;
	for(int S=0;S<(1<<n);S++)if(f[S]){
		//memset(sum,0,sizeof sum);
		int sum;
		for(int j=0;j<n;j++)if(!(S>>j&1)){
			sum=0;
			for(int k=0;k<n;k++)if(!(S>>k&1))
				sum-=d[j][k];
				if(sum<0)f[S|(1<<j)]=1;
		}	
	}
	vector<int>anss;	
	for(int i=0;i<n;i++)if(f[((1<<n)-1)^(1<<i)])anss.push_back(i);
		if(anss.size())for(int i=0;i<anss.size();i++)printf("%d%c",anss[i]+1," \n"[i+1==anss.size()]);
	else puts("0");
}
int main(){
	int T;scanf("%d",&T);
	while(T--)sol();
	return 0;
}
