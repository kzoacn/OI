#include<cstdio>
#include<cctype>
#include<algorithm>
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
LL sum=0,cur=0;
int main(){
	while(~scanf("%d",&n)){
		sum=cur=0;
		for(int i=1;i<=n;i++)scanf("%d",&v[i].first);
		for(int i=1;i<=n;i++)scanf("%d",&v[i].second),sum+=v[i].second;
		sort(v+1,v+1+n);
		for(int i=1;i<=n;i++){
			if(((cur+v[i].second)<<1LL)>=sum){
				printf("%d\n",v[i].first);
				break;
			}cur+=v[i].second;
		}
	}
	return 0;
}
