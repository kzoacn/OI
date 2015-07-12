#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
int a[1010],b[1010];
int n,p;
LL make(){
	LL res=0,ans=-(1LL<<61);
	for(int i=1;i<=n;i++){
		res+=a[i];
		if(res<0){
			res=0;
		}else{
			ans=max(ans,res);
		}
	}return ans;
}
void sol(){
	scanf("%d%d",&n,&p);
	if(n==1){
		cout<<p<<endl;
		return;
	}
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=a[i];
	LL ans=-(1LL<<61);
	ans=max(*max_element(a+1,a+1+n),p);
	for(int i=1;i<=n;i++){
		a[i]=p;
		ans=max(make(),ans);
		a[i]=b[i];
	}cout<<ans<<endl;
}
int main(){
	int T;scanf("%d",&T);	
	while(T--)sol();
	return 0;
}
