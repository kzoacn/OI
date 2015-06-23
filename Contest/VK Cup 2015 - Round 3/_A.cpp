#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
typedef long long LL;
int n,m;
struct se{
	int l,r,c,id;
	int len(){return r-l;}
}a[maxn],b[maxn];
se operator&(se A,se B){
	if(A.l>B.l)swap(A,B);
	return (se){max(B.l,A.l),min(A.r,B.r),0,0};
}
se operator|(se A,se B){
	return (se){min(A.l,B.l),max(A.r,B.r),0,0};
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i].l,&a[i].r),a[i].id=i;
	for(int i=1;i<=m;i++)scanf("%d%d%d",&b[i].l,&b[i].r,&b[i].c),b[i].id=i;
	LL ans=0,x,y;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		LL res=(LL)(a[i]&b[j]).len()*b[j].c;
		if(res>ans)ans=res,x=i,y=j;
	}
	cout<<ans<<endl;
	if(ans)cerr<<x<<" "<<y<<endl;
	return 0;
}
