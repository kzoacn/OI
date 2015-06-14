#include<bits/stdc++.h>
using namespace std;
const int maxn=50010;
int n;
int a[maxn];
long long sum=0;
int next(int i){return i+1<=n?i+1:1;}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),sum+=a[i];
	int i=1,j=2;
	long long cur=a[1];
	long long ans=0;
	for(;i<=n;){
 		while(2*(cur+a[j])<=sum)
 			cur+=a[j],j=next(j);
   		ans=max(ans,min(cur,sum-cur));
		cur-=a[i];i++;
		if(i==j)cur+=a[j],j=next(j);
	}cout<<ans<<endl;
	return 0;
}
