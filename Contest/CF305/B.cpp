#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+4;
int n;
int a[maxn],id[maxn],vis[maxn];
bool byA(int x,int y){return a[x]>a[y];}
int fa[maxn],siz[maxn];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int x,int y){
	x=find(x);y=find(y);
	if(x!=y)fa[x]=y,siz[y]+=siz[x];
}
int anss[maxn],cur;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)id[i]=i,siz[i]=1,fa[i]=i;
	sort(id+1,id+1+n,byA);
	cur=1;
	for(int i=1;i<=n;i++){
		vis[id[i]]=1;
		if(id[i]>1&&vis[id[i]-1])merge(id[i],id[i]-1);
		if(id[i]<n&&vis[id[i]+1])merge(id[i],id[i]+1);
		int sz=siz[find(id[i])];
		while(cur<=sz)
			anss[cur]=a[id[i]],cur++;
	}
	for(int i=1;i<=n;i++)printf("%d%c",anss[i]," \n"[i==n]);
	return 0;
}
