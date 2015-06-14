#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<climits>
using namespace std;
const int maxn=2015;
int n,h;
int f[maxn];
pair<int,int> a[maxn];
bool cmp(pair<int,int>x,pair<int,int>y){return x.first+x.second<y.first+y.second;}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i].first,&a[i].second);
	scanf("%d",&h);
	sort(a+1,a+1+n,cmp);
	memset(f,-1,sizeof f);f[0]=0;
	for(int i=1;i<=n;i++)f[0]+=a[i].first;
	int k=0;
	for(int i=1;i<=n;i++)
	for(int j=k;j>=0;j--){
		if(f[j]+a[i].second>=h)
			f[j+1]=max(f[j+1],f[j]-a[i].first);
		k+=f[k+1]>=0;
	}cout<<k<<endl;
	return 0;
}
