#include<cstdio>
#include<map>
#include<iostream>
#include<algorithm>
using namespace std;
const int mo=1000000007;
typedef long long LL;
LL n,m,P,Q;
namespace BF{
	int mp[22][22];
	int ans=0;
	int check(){
		int cur=0,sum=0;
		for(int i=1;i<=n;i++){
			cur=0;sum=0;
			for(int j=1;j<=m;j++){
				if(mp[i][j])cur++;
				else cur=0;
				if(cur>=P)return 0;
			}
		}
		int res=0;
		for(int j=1;j<=m;j++){
			sum=0;
			for(int i=1;i<=n;i++)sum+=mp[i][j];
			if(sum==n)res++;
			if(res>Q)return 0;
		}return 1;
	}
	void dfs(int x,int y){
		if(y==m+1)x++,y=1;
		if(x==n+1){
			ans+=check();
			return;
		}
		mp[x][y]=1;
		dfs(x,y+1);
		mp[x][y]=0;
		dfs(x,y+1);
	}
	int solve(){
		dfs(1,1);
		cout<<ans<<endl;
		return 0;
	}
}
namespace DP{
	struct info{
		int S,Q,P1,P2;
		bool operator<(const info &o)const{
			if(S!=o.S)return S<o.S;
			if(Q!=o.Q)return Q<o.Q;
			if(P1!=o.P1)return P1<o.P1;
			return P2<o.P2;
		}
		info(int S,int Q,int P1,int P2):S(S),Q(Q),P1(P1),P2(P2){}
	};
	map<info,int>dp[2];
	void up(int &x,int y){x+=y;x%=mo;}
	int solve(){
		int cur=0;
		dp[cur][info(0,0,0,0)]=1;
		for(int i=1;i<=n;i++){
			cur^=1;dp[cur].clear();
			for(int j=0;j<4;j++){
				if(j==0){
					
				}else
				if(j==1){
				
				}else
				if(j==2){
				
				}else
				if(j==3){
				
				}
			}
		}
		return 0;
	}
}
int main(){
	freopen("line.in","r",stdin);
	freopen("line.out","w",stdout);
	LL inv2=(1+mo)/2;
	cin>>n>>m>>P>>Q;
	if(P==1)return puts("1"),0;
	if(n*m<=20)return BF::solve();
	if(n==1){
		if(Q==1)return cout<<(m+1)%mo<<endl,0;
		if(P==2){
			if(Q==2)cout<<(2+m%mo*(m-1)%mo*inv2%mo)%mo<<endl;
		}
		if(P==3){
			if(Q==2)cout<<((2+m%mo*(m-1)%mo*inv2%mo)%mo+(m-1))%mo<<endl;
		}
	}
	return 0;
}
