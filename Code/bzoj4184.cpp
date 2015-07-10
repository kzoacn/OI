#include<bits/stdc++.h>
using namespace std;
const int maxn=500001;
struct LB{
	int lb[32],siz;
	LB(){memset(lb,0,sizeof lb);siz=0;}
	void insert(int x){
		if(full())return;
		for(int i=31;i>=0;i--)if(x>>i&1){
			if(lb[i])x^=lb[i];
			else{
				lb[i]=x;
				siz++;
				break;
			}
		}	
	}
	int Qmax(){
		int ans=0;
		for(int i=31;i>=0;i--)
			ans=max(ans,ans^lb[i]);
		return ans;
	}
	bool full(){
		return siz==31;
	}
};
LB operator+(LB A,const LB &B){
	for(int i=0;i<32;i++)if(B.lb[i])
		A.insert(B.lb[i]);
	return A;
}
int in(){
	int r=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:1,c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r*f;
}
int n;
int a[maxn];
LB lb[maxn];
int del[maxn];
vector<int> solve(int l,int r){
	if(l==r){
		vector<int>vec;
		if(a[l]>0)vec.push_back(a[l]);
		return vec;
	}
	int mid=(l+r)>>1;
	vector<int>ins=solve(l,mid);
	for(int i=mid+1;i<=r;i++)if(a[i]<0)
		del[++del[0]]=-a[i];
	sort(del+1,del+1+del[0]);
	LB ba;int cur=1;
	vector<int>rem;
	for(int i=0;i<ins.size();i++){
		if(ins[i]==del[cur])cur++;
		else{
			ba.insert(ins[i]);
			rem.push_back(ins[i]);
		}
	}
	for(int i=r;i>=mid+1;i--){
		lb[i]=lb[i]+ba;
		if(a[i]<0)ba.insert(-a[i]);
	}
	ins=solve(mid+1,r);
	for(int i=0;i<ins.size();i++)rem.push_back(ins[i]);
	sort(rem.begin(),rem.end());
	return rem;
}
int main(){
	freopen("bzoj4184.in","r",stdin);
	n=in();
	for(int i=1;i<=n;i++)a[i]=in();
	solve(1,n);
	for(int i=1;i<=n;i++)
		printf("%d\n",lb[i].Qmax());
	return 0;
}
