#include<bits/stdc++.h>
using namespace std;
int f[233][233];
int main(){
	freopen("tab.txt","w",stdout);
	//f[1][0]=f[1][1]=f[1][2]=1;
	f[0][0]=1;
	for(int i=1;i<=200;i++)
	for(int j=0;j<=2*i;j++){
		f[i][j]=f[i-1][j];
		if(j>=1)f[i][j]+=f[i-1][j-1];
		if(j>=2)f[i][j]+=f[i-1][j-2];
	//	f[i][j]%=3;
	}
	for(int i=0;i<=4;i++)
	for(int j=0;j<=i*2;j++)
		printf("%d%c",f[i][j]," \n"[j==2*i]);
	return 0;
}
