#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=1e5+5;
int sum[9][maxn];
int n,k;
struct P{int x,k;bool operator<(const P &o)const{return x<o.x;}}p[maxn];
bool check(int l,int r){
	int cnt=0,same=0;
	for(int i=1;i<=8;i++){
		int cot=sum[i][r]-sum[i][l-1];
		if(cot){
			cnt++;
			if(!same)same=cot;
			else if(same!=cot)
				return false;
		}
	}return cnt>=k;
}
int main(){
	freopen("long.in","r",stdin);
	freopen("long.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&p[i].x,&p[i].k);
	sort(p+1,p+1+n);
	for(int i=1;i<=n;i++)sum[p[i].k][i]++;
	for(int j=1;j<=8;j++)
	for(int i=1;i<=n;i++)
	sum[j][i]+=sum[j][i-1];
	int ans=0;
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)
	if(check(i,j))
	ans=max(ans,p[j].x-p[i].x);
	cout<<ans<<endl;
	return 0;
}
