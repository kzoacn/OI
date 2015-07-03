#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1e6+6;
int a[maxn],n;
LL dp[maxn];
struct node{
	int mx,mn;
	int l,r;
	void rz();
}t[maxn<<2];
void node::rz(){
	mx=max(t[l].mx,t[r].mx);
	mn=min(t[l].mn,t[r].mn);
}
int tot=0;
int build(int l,int r){
	int x=++tot;
	if(l==r){
		t[x].mx=t[x].mn=a[l];
		return x;
	}
	t[x].l=build(l,(l+r)/2);
	t[x].r=build((l+r)/2+1,r);
	t[x].rz();
	return x;
}
int Qmax(int x,int l,int r,int l0,int r0){
	if(l0<=l&&r0>=r)return t[x].mx;
	int ans=INT_MIN;
	if(l0<=(l+r)/2)ans=max(ans,Qmax(t[x].l,l,(l+r)/2,l0,r0));
	if(r0>(l+r)/2)ans=max(ans,Qmax(t[x].r,(l+r)/2+1,r,l0,r0));
	return ans;
}
int Qmin(int x,int l,int r,int l0,int r0){
	if(l0<=l&&r0>=r)return t[x].mn;
	int ans=INT_MAX;
	if(l0<=(l+r)/2)ans=min(ans,Qmin(t[x].l,l,(l+r)/2,l0,r0));
	if(r0>(l+r)/2)ans=min(ans,Qmin(t[x].r,(l+r)/2+1,r,l0,r0));
	return ans;
}
int Qsum(int l,int r){return Qmax(1,1,n,l,r)-Qmin(1,1,n,l,r);}
deque<int>dq;
LL calc(int j,int i){
	return dp[j-1]+Qsum(j,i);
}
int BF(){
	for(int i=2;i<=n;i++)
	for(int j=1;j<i;j++)
		dp[i]=max(dp[i],calc(j,i));
	cout<<dp[n]<<endl;
	return 0;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	build(1,n);
//	if(n<=1000)return BF();
	dq.push_back(1);
	for(int i=2;i<=n;i++){
		LL tmp=calc(dq.back(),i);
		dq.pop_back();
		while(dq.size()>1)
		
		while(dq.size()>1&&
			calc(dq[0],i)<=calc(dq[1],i))dq.pop_front();
		dp[i]=calc(dq.front(),i);
		dq.push_back(i);
	}cout<<dp[n]<<endl;
	return 0;
}
