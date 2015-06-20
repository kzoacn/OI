#include<bits/stdc++.h>
using namespace std;
const int maxn=1e7+2;
int n,m,p,q;
int fa[maxn];
int find(int x){return fa[x]==x?x:find(fa[x]);}
void merge(int x,int y){fa[find(x)]=find(y);}
int col[maxn];
int main(){
	cin>>n>>m>>p>>q;
	for(int i=1;i<=n+1;i++)fa[i]=i;
	for(int i=m;i>=1;i--){
		int l=(i*p+q)%n+1;
		int r=(i*q+p)%n+1;
		if(l>r)swap(l,r);
		int j=find(l);
		for(;j<=r;){
			col[j]=i;
			merge(j,r+1);
			j=find(j+1);
		}
	}for(int i=1;i<=n;i++)printf("%d\n",col[i]);
	return 0;
}
