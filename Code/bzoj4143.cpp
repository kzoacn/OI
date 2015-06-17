#include<bits/stdc++.h>
using namespace std;
const int maxn=500010;
int n,m;
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
int a[maxn],b[maxn],d[maxn];
vector<int>da[21];
bool cmp(int x,int y){return a[x]!=a[y]?a[x]<a[y]:b[x]<b[y];}
bool cm(int x,int y){return x<a[y];}
void compute(vector<int>&da){
	sort(da.begin(),da.end(),cmp);
	for(int i=0;i+1<da.size();i++){
		int j=upper_bound(da.begin(),da.end(),b[da[i]],cm)-da.begin();
		if(j<da.size()){
			printf("TAK %d %d\n",da[i],da[j]);
			return;	
		}
	}puts("NIE");
}
int main(){
	freopen("bzoj4143.in","r",stdin);
	n=in();m=in();
	for(int i=1;i<=n;i++)a[i]=in(),b[i]=in(),d[i]=in(),da[d[i]].push_back(i);
	for(int i=1;i<=m;i++)
		compute(da[i]);
	return 0;
}
