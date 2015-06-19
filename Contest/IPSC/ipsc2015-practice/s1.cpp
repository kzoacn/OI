#include<bits/stdc++.h>
using namespace std;
int calc(vector<int>v){
	static int vis[int(150001)];
	int n=v.size();
	for(int i=1;i<=n;i++)vis[i]=0;
	int ans=1;vis[0]=1;
	for(int i=0;i<n;i++){
		vis[v[i]]=1;
		if(!vis[v[i]-1])
			ans++;
	}return ans;
}
void sol(){
	int n;scanf("%d",&n);
	vector<int>vec[4];
	for(int i=1;i<=n*4;i++){
		char s[10];
		int x;
		scanf("%s",s);
		char c=s[0];
		sscanf(s+1,"%d",&x);
		if(c=='H')c=0;
		if(c=='D')c=1;
		if(c=='S')c=2;
		if(c=='C')c=3;
		vec[c].push_back(x);
	}
	cout<<max(max(calc(vec[0]),calc(vec[1])),max(calc(vec[2]),calc(vec[3])))<<endl;
} 
int main(){
	freopen("s2.in","r",stdin);
	freopen("s2.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--)sol();
	return 0;
}
