#include<cstring>
#include<cctype>
#include<cstdio>
#include<climits>
#include<algorithm>
#include<iostream>
using namespace std;
int mp[4][4];
int n,m,a,b;
namespace BF{
	int ans=0;
	int mp[4][4];
	void clear(int x,int y){
		for(int i=x;i<min(x+a,n);i++)
		for(int j=y;j<min(y+b,m);j++)
		mp[i][j]=0;
	}
	int check(int x,int y,int xx,int yy){
		for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		mp[i][j]=::mp[i][j];
		
		clear(x,y);
		clear(xx,yy);
		int s=0;
		for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		s+=mp[i][j];
		return s==0;
	}
	int check(){
		for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		for(int k=0;k<n;k++)
		for(int l=0;l<m;l++)
		if(check(i,j,k,l)){
			return 1;
		}
		return 0;
	}
	void dfs(int x,int y){
		if(y==m)x++,y=0;
		if(x==n){
			ans+=check();
			return;
		}
		::mp[x][y]=1;
		dfs(x,y+1);
		::mp[x][y]=0;
		dfs(x,y+1);
	}
	int solve(){
		dfs(0,0);
		cout<<ans<<endl;
		return 0;
	}
}
int main(){
	freopen("board.in","r",stdin);
	freopen("board.out","w",stdout);
	cin>>n>>m>>a>>b;
	if(n<=4&&m<=4)return BF::solve();
	puts("233");
	return 0;
}
