#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
typedef long long LL;
int a[maxn],b[maxn];
int n;
LL f[maxn][2];
LL c[maxn];
int main(){
	scanf("%d",&n);	
	int mx=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[a[i]]++;mx=max(mx,a[i]);
	}
	for(int i=1;i<=mx;i++)c[i]=(LL)i*b[i];
	for(int i=1;i<=mx;i++){
		f[i][1]=f[i-1][0]+c[i];
		f[i][0]=max(f[i-1][1],f[i-1][0]);
	}
	cout<<*max_element(&f[0][0],&f[maxn][2])<<endl;
	return 0;
}
