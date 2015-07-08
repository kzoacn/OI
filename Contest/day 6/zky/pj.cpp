#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
char s[maxn],*cur=s;
int n,a[maxn];
int psum[maxn],ssum[maxn];
struct sgt{
	struct node{
		int mn;
		node *l,*r;
		void rz(){
			mn=min(r->mn,l->mn);
		}
	}pool[maxn*2],*rt,*cur=pool;
	node* newnode(){
		return cur++;
	}
	node* build(int *a,int l,int r){
		node *x=newnode();
		if(l==r){x->mn=a[l];return x;}
		x->l=build(a,l,(l+r)/2);
		x->r=build(a,(l+r)/2+1,r);
		x->rz();
		return x;
	}
	void build(int *a){rt=build(a,1,n);}
	int Qmin(node *x,int l,int r,int l0,int r0){
		if(l0<=l&&r0>=r)return x->mn;
		int mid=(l+r)>>1,ans=INT_MAX;
		if(l0<=mid)ans=min(ans,Qmin(x->l,l,(l+r)/2,l0,r0));
		if(r0>mid)ans=min(ans,Qmin(x->r,(l+r)/2+1,r,l0,r0));
		return ans;
	}
	int Qmin(int l,int r){return Qmin(rt,1,n,l,r);}
}T1,T2;
bool check(int l,int r){
	int ans1=T1.Qmin(l,r);
	if(ans1-psum[l-1]<0)return false;
	int ans2=T2.Qmin(l,r);
	if(ans2-ssum[r+1]<0)return false;
	return true;
}
bool pcheck(int l,int r){
	int ans1=T1.Qmin(l,r);
	if(ans1-psum[l-1]<0)return false;
	return true;
}
bool scheck(int l,int r){
	int ans2=T2.Qmin(l,r);
	if(ans2-ssum[r+1]<0)return false;
	return true;
}
int nxt[maxn];
int one[maxn];
int main(){
	freopen("pj.in","r",stdin);
	freopen("pj.out","w",stdout);
	scanf("%d",&n);
	*++cur=getchar();
	while(!isalpha(*cur))*cur=getchar();
	while(isalpha(*cur))*++cur=getchar();*cur='\0';
	for(int i=1;i<=n;i++)a[i]=(s[i]=='p'?1:-1);
	for(int i=1;i<=n;i++)psum[i]=psum[i-1]+a[i];
	for(int i=n;i>=1;i--)ssum[i]=ssum[i+1]+a[i];
	for(int i=1;i<=n;i++){
		if(a[i]==1){
			one[++one[0]]=i;
		}
	}
	T1.build(psum);
	T2.build(ssum);
	int ans=0;
	int T=0;
	for(int i=1;i<=one[0];i++){
		int l=one[i];
		int j=lower_bound(one+1,one+1+one[0],l+ans)-one;
		if(T>3e5)break;
		for(;j<=one[0];j++){
			int r=one[j];
			if(++T>3e5)break;
			if(!pcheck(l,r))break;
			if(check(l,r)){				
				if(r-l+1>ans)
				ans=max(ans,r-l+1);
			}
		}
	}


	for(int i=one[0];i>=1;i--){
		int r=one[i];
		int j=lower_bound(one+1,one+1+one[0],r-ans)-one;
		if(T>6e5)break;
		for(;j>=1;j--){
			int l=one[j];
			if(++T>6e5)break;
			if(!scheck(l,r))break;
			if(check(l,r)){
				if(r-l+1>ans)
				ans=max(ans,r-l+1);
			}
		}
	}
	
	
	
	
	
	cout<<ans<<endl;
	return 0;
}
