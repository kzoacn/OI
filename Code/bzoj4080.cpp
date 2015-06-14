#include<bits/stdc++.h>
using namespace std;
int n,d;
int x[101],y[101];
vector<int>G[101];
int sqr(int x){return x*x;}
int f[101],mp[101][101];
vector<int>alt[101],S,U,A;
bool dfs(int u){
	if(clock()>1900){
		cout<<A.size()<<endl;
		exit(0);
	}
	if(!alt[u].size()){
		if(A.size()<U.size()){A=U;return 1;}
		return 0;	
	}
	if(U.size()+f[u]<=A.size())return 0;
	if(U.size()+alt[u].size()<=A.size())return 0;
	for(int i=0;i<alt[u].size();i++){
		int v=alt[u][i];alt[v].clear();
		for(int j=i+1;j<alt[u].size();j++){
			int w=alt[u][j];
			if(!mp[v][w])continue;
			alt[v].push_back(w);
		}
		U.push_back(v);
		if(dfs(v))return 1;
		U.pop_back();
	}return 0;
}
int getn(){
	int res=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
int main(){
	freopen("test.txt","w",stderr);
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++)x[i]=getn(),y[i]=getn();
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)
		if(sqr(x[i]-x[j])+sqr(y[i]-y[j])<=d*d)
			G[i].push_back(j),G[j].push_back(i),mp[i][j]=mp[j][i]=1,cerr<<i<<" "<<j<<endl;
	for(int i=1;i<=n;i++)sort(G[i].begin(),G[i].end());
	f[n]=1;A.push_back(n);
	for(int i=n-1;i>=1;i--){
		alt[i].clear();
		U.clear();U.push_back(i);
		for(int j=0;j<G[i].size();j++)if(G[i][j]>i)
		alt[i].push_back(G[i][j]);
		f[i]=n-i;
		dfs(i);
		f[i]=A.size();
	}
	printf("%d\n",A.size());
//	for(int i=0;i<A.size();i++)
//	printf("%d%c",A[i]," \n"[i+1==A.size()]);
	return 0;
}
