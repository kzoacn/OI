#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
typedef long long LL;
LL h[maxn],p[maxn];
int n,m;
LL in(){
	LL r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
LL S(LL p1,LL p2,LL h){
	if(p2<=h){
		return h-p1;	
	}else if(p1>=h){
		return p2-h;
	}else{
		return min(2*(h-p1)+p2-h,h-p1+2*(p2-h));
	}
}
bool check(LL lim){
	int cur=1;
	for(int i=1;i<=n;i++){
//		if(S(p[cur],p[cur],h[i])>lim)return false;
		int flag=cur;
		while(cur<=m&&S(p[flag],p[cur],h[i])<=lim)
			cur++;
		if(cur==m+1)return true;
	}return false;
}
int main(){
	freopen("C.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)h[i]=in();
	for(int i=1;i<=m;i++)p[i]=in();
	LL l=0,r=(p[m]-p[1]+abs(h[1]-p[1]))+233;
	while(l<r){
		LL mid=(l+r)/2;
		if(check(mid))
			r=mid;
		else l=mid+1;
	}cout<<r<<endl;
	return 0;
}
