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
	freopen("max.in","r",stdin);
	freopen("max.out","w",stdout);
	n=in();m=in();int tot=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	a[i][j]=in(),p[++tot]=(P){i,j,a[i][j]};
	sort(p+1,p+1+tot,cmp);
	for(int i=1;i<=tot;i++){
		int x=p[i].x,y=p[i].y;
		for(int j=1;j<i;j++){
			if(vis[x][p[j].y]&&vis[p[j].x][y]){
				cout<<p[i].w<<endl;
				return 0;
			}
		}vis[x][y]=1;
	}
	return 0;
}
