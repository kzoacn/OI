#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m;
double mp[101][101];
double w[101][101];
double I[101];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)mp[i][j]=1e15;
	int x,y;double z;
	for(int i=1;i<=m;i++){
		scanf("%d%d%lf",&x,&y,&z);
		mp[x][y]=mp[y][x]=z;
		w[x][y]=w[y][x]=1;
	}
	for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
	if(mp[i][k]+mp[k][j]<mp[i][j]){mp[i][j]=mp[i][k]+mp[k][j];w[i][j]=0;}
	if(mp[i][k]+mp[k][j]==mp[i][j])w[i][j]+=w[i][k]*w[k][j];}
    for(int i=1;i<=n;i++)w[i][i]=0;
    for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
        if(mp[i][k]+mp[k][j]==mp[i][j]&&w[i][j]>0)
        I[k]+=w[i][k]*w[k][j]/w[i][j];
    }for(int i=1;i<=n;i++)printf("%.3lf\n",I[i]);
	return 0;
}
