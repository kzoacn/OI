#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=1e5+5;
int n,m;
int a[maxn],b[maxn];
priority_queue<int>Q1;
priority_queue<int>Q2;
void sol(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		Q1.push(a[i]);
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&b[i]);
		Q2.push(-b[i]);
	}
	long long ans=0;
	while(1){
		int t1=Q1.top();Q1.pop();
		int t2=Q2.top();Q2.pop();
		if(t1+t2>0){
			ans+=t1+t2;
			Q1.push(t2);
			Q2.push(t1);
		}else break;
	}cout<<ans<<endl;
	while(!Q1.empty())Q1.pop();
	while(!Q2.empty())Q2.pop();
}
int main(){
	freopen("B.in","r",stdin);
	int T;scanf("%d",&T);
	while(T--)sol();
	return 0;
}
