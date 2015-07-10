#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=1010;
int n,m;
int a[maxn][maxn];
int in(){
	int r=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r*f;
}
struct P{int x,y,w;bool operator<(const P &o)const{return x!=o.x?x<o.x:y<o.y;}}p[maxn*maxn];
bool vis[maxn][maxn];
bool cmp(const P &a,const P &b){return a.w>b.w;}
int main(){
//	freopen("max.in","r",stdin);
	n=in();m=in();int tot=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	a[i][j]=in();
	int ans=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	for(int k=i+1;k<=n;k++)
	for(int l=j+1;l<=n;l++)
	ans=max(ans,min(min(a[i][j],a[k][l]),min(a[i][l],a[k][j])));
	cout<<ans<<endl;
	return 0;
}
