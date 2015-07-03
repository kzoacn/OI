#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int son[maxn][26];
int tot,val[maxn];
int vis[maxn],f[maxn],g[maxn];
#define id(c) (c-'a')
void insert(int len,char *s){
	int u=0;
	for(int i=0;i<len;i++){
		if(!son[u][id(s[i])])son[u][id(s[i])]=++tot;
		u=son[u][id(s[i])];
	}val[u]=1;
}
void dfs(int u){
	if(vis[u])return ;
	int v;vis[u]=1;
	for(int i=0;i<26;i++)if(v=son[u][i])dfs(v);
	
	for(int i=0;i<26;i++)if(v=son[u][i]){
		
	}
	
}
int n,k;
char s[maxn];
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		insert(strlen(s),s);
	}
	dfs(0);
	
	if(f[0]&&g[0]){
		puts("First");
	}else
	if(f[0]){
		puts(k%2?"First":"Second");
	}else
	if(g[0]){
		puts("Second");
	}else{
		puts("233");
	}
	return 0;
}
