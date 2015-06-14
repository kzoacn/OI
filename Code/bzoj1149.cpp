#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n;
int c[maxn][2],siz[maxn];
int ans=0,mind[maxn],maxd[maxn],goo[maxn];
void dfs(int x){
	if(c[x][0])dfs(c[x][0]);
	if(c[x][1])dfs(c[x][1]);
	if(ans==-1)return;
	ans+=siz[c[x][0]]<siz[c[x][1]];
	mind[x]=min(mind[c[x][0]],mind[c[x][1]])+1;
	maxd[x]=max(maxd[c[x][0]],maxd[c[x][1]])+1;
	siz[x]=siz[c[x][0]]+1+siz[c[x][1]];
	goo[x]=siz[c[x][0]]==siz[c[x][1]]&&mind[x]==maxd[x];
	if(maxd[x]-mind[x]>1)ans=-1;
	if(!goo[c[x][0]]&&!goo[c[x][1]])ans=-1;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&c[i][0],&c[i][1]),c[i][0]=c[i][0]==-1?0:c[i][0],c[i][1]=c[i][1]==-1?0:c[i][1];
	for(int i=0;i<=n;i++)goo[i]=1;
	dfs(1);
	cout<<ans<<endl;
	return 0;
} 
