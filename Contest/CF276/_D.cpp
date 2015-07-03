#include<bits/stdc++.h>
#define Max(l,r) (*max_element(a+l,a+r+1))
#define Min(l,r) (*min_element(a+l,a+r+1))
using namespace std;
typedef long long LL;
const int maxn=1e6+6;
int a[maxn],n;
LL dp[maxn];
int main(){
//	freopen("D.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	
	static vector<int>vec;
	for(int i=1;i<=n;i++){
		int k=i;
		for(int j=1;j<i;j++){
			LL tmp=dp[j-1]+Max(j,i)-Min(j,i);
			cerr<<tmp<<" ";
			if(tmp>dp[i]){
				k=j;
				dp[i]=tmp;
			}
		}cerr<<endl;
		vec.push_back(k);
	}
	
	assert(is_sorted(vec.begin(),vec.end()));
	
	cout<<dp[n]<<endl;
	return 0;
}
