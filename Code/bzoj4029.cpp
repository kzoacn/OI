#include<bits/stdc++.h>
using namespace std;
int T,L,R;
int ten[10];
int lowten(int x){
	int y=0;
	while(x%10==0)x/=10,y++;
	return ten[y];
}
int len(int x){
	int y=0;
	while(x)x/=10,y++;
	return y;
}
int calc(int x){
	while(x%10==0)x/=10;
	return len(x)*2-(x%10==5);
}
void solve(){
	scanf("%d%d",&L,&R);
	int res=L,ans=L;
	while(res<=R){
		if(calc(res)<calc(ans))ans=res;
		res+=lowten(res);
	}printf("%d\n",ans);
}
int main(){
	ten[0]=1;for(int i=1;i<10;i++)ten[i]=ten[i-1]*10;
	scanf("%d",&T);	
	while(T--)solve();
	return 0;
}
