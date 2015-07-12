#include<bits/stdc++.h>
using namespace std;
const int maxn=500001;
struct LB{
	int lb[32];
	LB(){memset(lb,0,sizeof lb);}
	void insert(int x){
		for(int i=31;i>=0;i--)if(x>>i&1){
			if(lb[i])x^=lb[i];
			else{
				lb[i]=x;
				break;
			}
		}	
	}
	int Qmax(){
		int ans=0;
		for(int i=31;i>=0;i--)if(lb[i])
			ans=max(ans,ans^lb[i]);
		return ans;
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
struct node{
	LB lb;
}t[maxn*2];
int tot=0;
#define ls x+1
#define rs x+r-l+2-((r^l)&1)
void Add(int x,int l,int r,int l0,int r0,int y){
	if(l0<=l&&r0>=r){t[x].lb.insert(y);return;}
	int mid=(l+r)>>1;
	if(l0<=mid)Add(ls,l,mid,l0,r0,y);
	if(r0>mid)Add(rs,mid+1,r,l0,r0,y);
}
void push(int x,int l,int r){
	if(l==r){
		//anss[l]=t[x].lb.Qmax();
		printf("%d\n",t[x].lb.Qmax());
		return;
	}
	int mid=(l+r)>>1;
	t[ls].lb=t[ls].lb+t[x].lb;
	t[rs].lb=t[rs].lb+t[x].lb;
	push(ls,l,mid);
	push(rs,mid+1,r);
}

int main(){
	cerr<<sizeof(t)/1024.0/1024.0<<endl;
	freopen("bzoj4184.in","r",stdin);
	n=in();
	for(int i=1;i<=n;i++)a[i]=in();
	
	
//	build(1,n);
	
	multimap<int,int>M;
	for(int i=1;i<=n;i++){
		if(a[i]>0){
			M.insert(make_pair(a[i],i));
		}else{
			multimap<int,int>::iterator it;
			it=M.find(-a[i]);
			Add(1,1,n,it->second,i-1,-a[i]);
			M.erase(it);
		}
	}
	
	while(!M.empty()){
		multimap<int,int>::iterator it;
		it=M.begin();
		Add(1,1,n,it->second,n,it->first);		
		M.erase(it);
	}
	
	push(1,1,n);
	return 0;
}
