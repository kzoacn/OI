#include<bits/stdc++.h>
using namespace std;
const int maxn=1e7+5;
typedef long long LL;
int n;
struct par{
	int first,second;
	bool operator<(const par o)const{
		return first==o.first?second<o.second:first<o.first;
	}
};	
par v[maxn];
LL sum=0;
unsigned int rnd(){
	static unsigned int x=23;
	return x=17*x+13;
}
int md;
bool part(par x){
	return x.first<md;
}
int main(){
	while(~scanf("%d",&n)){
		for(int i=1;i<=n;i++)scanf("%d",&v[i].first);
		for(int i=1;i<=n;i++)scanf("%d",&v[i].second),sum+=v[i].second;
		int l=1,r=n;
		LL tmp=0;
		while(l<r){
			LL cur=0;
			int x=(l+r)/2;
			md=v[x].first;
			int pos=partition(v+l,v+r+1,part)-v-1;
			for(int i=l;i<=pos;i++)cur+=v[i].second;
			if((tmp+cur)*2<sum)
				l=pos+1,tmp+=cur;
			else r=pos;
		}printf("%d\n",v[l-1].first);
	}
	return 0;
}
