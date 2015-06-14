#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+6;
typedef long long LL;
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
int n;
struct seg{
	int l,r;
	seg(int l=0,int r=0):l(l),r(r){}
	bool operator<(const seg &oth)const{return l!=oth.l?l<oth.l:r>oth.r;}
	bool operator==(const seg &oth)const{return l==oth.l&&r==oth.r;}
}se[maxn];
seg operator|(seg A,seg B){
	return seg(min(A.l,B.l),max(A.r,B.r));
}
seg operator&(seg A,seg B){
	if(A.l>B.l)swap(A,B);
	return seg(B.l,A.r);
}
LL ans=0;
void update(seg A,seg B){
	if(A.l>B.l)swap(A,B);
	ans=max(ans,(LL)(A.r-B.l)*(B.r-A.l));
}
LL calc(seg A,seg B){
	return (LL)(A.r-B.l)*(B.r-A.l);
}
void solve(int l,int r,int x,int y){
	if(l>r||x>y)return;
	if(x==y){
		for(int i=l;i<=r;i++)if(i!=x)
			update(se[i],se[x]);
		return;
	}int mid=(l+r)>>1,ps=mid+1;
	for(int i=mid+1;i<=r;i++){
		if(calc(se[mid],se[i])>calc(se[mid],se[ps]))
			ps=i;
	}solve(l,mid-1,x,ps-1);
	solve(mid,r,ps,y);
}
int main(){
	n=in();
	for(int i=1;i<=n;i++)
		se[i].l=in(),se[i].r=in();
	sort(se+1,se+1+n);
	int top=1;
	for(int i=2,j=1;i<=n;i++){
		if((se[i]|se[top])==se[top]){
			update(se[i],se[top]);
		}else se[++top]=se[i];
	}n=top;
	solve(1,n,1,n);
	printf("%lld\n",ans);
	return 0;
}
