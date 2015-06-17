#include<bits/stdc++.h>
using namespace std;
int a[14];
int n;
bool calc(int S){
	int ans=0;
	for(int i=0;i<n;i++)if(S>>i&1)ans^=a[i];
	return ans==0;
}
void sol(){
	cin>>n;
	for(int i=0;i<n;i++)cin>>a[i];
	int flag=0;
	for(int S=1;S<(1<<n);S++){
		if(calc(S)){flag=1;break;}
	}puts(flag?"NO":"YES");
}
int main(){
	int T=10;
	while(T--)sol();
	return 0;
}
