#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
vector<int>d[maxn];
int notp[maxn];
pair<int,int>a[maxn];
int main(){
	for(int i=2;i<maxn;i++){
		if(!notp[i]){
			for(int j=i;j<maxn;j+=i){
				notp[j]=1;
				d[j].push_back(i);
			}
		}
	}
	for(int i=1;i<=100000;i++){
		a[i].first=accumulate(d[i].begin(),d[i].end(),1,multiplies<int>());
		a[i].second=i;
	}sort(a+1,a+1+100000);
	cout<<a[10000].second<<endl;
	return 0;
}
