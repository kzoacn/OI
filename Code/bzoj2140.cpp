#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
char s[20];
trie<string,int>M;
int z,n,m;
vector<int>G[4001];
int Link[8001],vis[8001],_Link[8001];
int fu,fv,man[4040],woman[4040];
int find(int u){
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];if(vis[v])continue;
		if(u==fu&&v==fv)continue;
		vis[v]=1;
		if(!Link[v]||find(Link[v])){
			Link[v]=u;return 1;
		}
	}return 0;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int u,v;
		scanf("%s",s);
		u=M[s]=i;
		scanf("%s",s);
		v=M[s]=i+n;
		G[u].push_back(v);
		Link[v]=u;
		_Link[v]=u;
		man[i]=u;woman[i]=v;
	}scanf("%d",&m);
	while(m--){
		int u,v;
		scanf("%s",s);
		u=M[s];
		scanf("%s",s);
		v=M[s];
		if(u>v)swap(u,v);
		G[u].push_back(v);
	}
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof vis);
		copy(_Link+n,_Link+n*2+1,Link+n);
		fu=man[i];
		fv=woman[i];
		Link[woman[i]]=0;		
		if(find(i))puts("Unsafe");
		else puts("Safe");
	}
	return 0;
}
