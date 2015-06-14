#include<bits/stdc++.h>
using namespace std;
int A[1001][1001];
int B[1001][1001];
int C[1001][1001];
int E[1001];
int X[1001],Y[1001],Z[1001];
int n;
int getint(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
int main(){
	srand(10086);
	while(~scanf("%d",&n)){
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)A[i][j]=getint();
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)B[i][j]=getint();
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)C[i][j]=getint();	
		for(int i=1;i<=n;i++)E[i]=rand()%1000;
		memset(X,0,sizeof X);memset(Y,0,sizeof Y);
		for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)X[i]+=C[i][k]*E[k];
		for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)Y[i]+=B[i][k]*E[k];
		for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)Z[i]+=A[i][k]*Y[k];
		if(vector<int>(X+1,X+1+1000)==vector<int>(Z+1,Z+1+1000))
			puts("Yes");
		else puts("No");
	}
	return 0;
}
