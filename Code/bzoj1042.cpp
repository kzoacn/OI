#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int c[4],d[4];
int tot;
LL f[100010],s;
int main(){
	cin>>c[0]>>c[1]>>c[2]>>c[3]>>tot;
	f[0]=1;
	for(int j=0;j<4;j++)
	for(int i=1;i<=100000;i++){if(i-c[j]>=0){
			f[i]+=f[i-c[j]];
		}
	}
	while(tot--){
		cin>>d[0]>>d[1]>>d[2]>>d[3]>>s;
		LL ans=0;
		for(int i=0;i<(1<<4);i++){
			LL cur=0;
			int cnt=0;
			for(int j=0;j<4;j++)if(i>>j&1){
				cur+=(LL)(d[j]+1)*c[j];
				cnt++;
			}
			LL res=s-cur>=0?f[s-cur]:0;
			if(cnt&1)ans-=res;
			else ans+=res;
		}printf("%lld\n",ans);
	}
	return 0;
}
