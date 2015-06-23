#include<bits/stdc++.h>
using namespace std;
int f[1001][101];
int n,T;
vector<int>h[101];
int main(){
	scanf("%d%d",&n,&T);
	for(int i=0;i<n;i++){
		int q,t;scanf("%d%d",&t,&q);
		h[T-t].push_back(q);
	}for(int i=0;i<T;i++)sort(h[i].begin(),h[i].end(),greater<int>());
	for(int i=T;i>=0;i--){
		for(int j=n;j>=0;j--){
			int sum=0;
			for(int k=0;k<h[i].size()&&k<j;k++){
				sum+=h[i][k];
				f[i][j]=max(f[i][j],f[i][j-k-1]+sum);  
			}
		}if(!i){cout<<f[0][1]<<endl;return 0;}
		else {
			for(int j=0;j<=n;j++)
				f[i-1][(j+1)/2]=max(f[i-1][(j+1)/2],f[i][j]);
		}
	}
	return 0;
}
