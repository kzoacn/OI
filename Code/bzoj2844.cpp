#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
const int BIT=31;
int a[maxn],n;
int b[BIT],c[BIT];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		for(int j=BIT-1;j>=0;j--){
			if(x&(1<<j)){
				if(b[j])x^=b[j];
				else {b[j]=x;break;}
			}
		}
	}c[0]=!!b[0];
	for(int i=1;i<BIT;i++)c[i]=c[i-1]+(!!b[i]);
	int m;scanf("%d",&m);
	long long ans=0;
	for(int i=BIT-1;i>=0;i--)
		if(m&(1<<i)){
			ans+=1<<c[i-1];
			ans%=10086;
		}
	cout<<ans<<endl;
	return 0;
}
