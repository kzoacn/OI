#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
typedef long long LL;
struct seg{
	LL l,r,id;
	bool operator<(const seg &o)const{
		return l!=o.l?l<o.l:r<o.r;
	}
}se[maxn],s[maxn];
pair<LL,LL> a[maxn];
LL n,m;
bool bycmp(seg a,seg b){
	return a.id<b.id;
}
bool by(pair<LL,LL> a,pair<LL,LL> b){
	return a.second<b.second;
}
int main(){
	scanf("%I64d%I64d",&n,&m);
	for(LL i=1;i<=n;i++)
		scanf("%I64d%I64d",&s[i].l,&s[i].r);
	for(LL i=1;i<=m;i++)scanf("%I64d",&a[i].first),a[i].second=i;
	for(LL i=1;i<n;i++){
		se[i].l=s[i+1].l-s[i].r;
		se[i].r=s[i+1].r-s[i].l;
		se[i].id=i;
	}sort(se+1,se+n);
	sort(a+1,a+1+m);
	LL cur=1;
	static LL anss[maxn];
	for(LL i=1;i<n;i++){
		if(a[cur].first>se[i].r)return puts("No"),0;
		while(cur<=m&&a[cur].first<se[i].l)cur++;
		if(cur>m)return puts("No"),0;
		if(a[cur].first<se[i].l)return puts("No"),0;
		if(a[cur].first>se[i].r)return puts("No"),0;
		anss[se[i].id]=a[cur].second;
		cur++;
	}
	sort(se+1,se+n,bycmp);
	sort(a+1,a+1+m,by);
	for(LL i=1;i<n;i++){
		LL l=a[anss[i]].first;
		if(l<se[i].l||se[i].r<l){
			exit(1);
			puts("No");
			return 0;
		}
	}
	
	puts("Yes");
	for(LL i=1;i<n;i++)
		printf("%I64d%c",anss[i]," \n"[i==n-1]);
	return 0;
}
