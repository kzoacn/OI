#include<bits/stdc++.h>
using namespace std;
const int maxn=233;
int col[maxn],n,ans;
// 1W 2Y 3R 4B
char mp[]={"QWYRB"};
int check(){
	static int rcol[maxn];
	for(int i=1;i<=n;i++)rcol[i]=col[n-i+1];
	for(int i=1;i<=n;++i)if(col[i]!=rcol[i])return 1;
	return 2;
}
void dfs(int x){
	if(x>n){
		ans+=check();
//		if(check())for(int i=1;i<=n;i++)printf("%c%c",mp[col[i]]," \n"[i==n]);
		return ;
	}
	for(int i=1;i<=4;i++){
		if(col[x-1]==i)continue;
		if(i<=2&&col[x-1]==3-i)continue;
		if(i>=3&&col[x-1]==7-i)continue;
		if(x>2){
			if(col[x-2]==4&&col[x-1]==1&&i==3)continue;
			if(col[x-2]==3&&col[x-1]==1&&i==4)continue;
		}
		col[x]=i;
		dfs(x+1);
	}
}
int f(int x){
	n=x;ans=0;
	dfs(1);
	return ans/2;
}
int l,r;
int main(){
	freopen("flag.in","r",stdin);
	freopen("flag.out","w",stdout);
	cin>>l>>r;
	int ans=0;
	for(int i=l;i<=r;i++)ans+=f(i);
	cout<<ans<<endl;
	return 0;
}
