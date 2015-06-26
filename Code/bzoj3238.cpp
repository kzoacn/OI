#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int son[maxn][26],len[maxn],tot=1,fa[maxn],last=1,cnt[maxn];
int newnode(int x){
	len[++tot]=x;
	return tot;
}
/*void add(int w){
	int p=last;
	int np=newnode(len[p]+1);
	while(p&&!son[p][w])son[p][w]=np,p=fa[p];
	if(!p)fa[np]=1;
	else{
		int q=son[p][w];
		if(len[p]+1==len[q])fa[np]=q;
		else{
			int nq=newnode(len[q]+1);
			memcpy(son[nq],son[q],sizeof son[nq]);
			fa[nq]=fa[q];fa[q]=fa[np]=nq;
			while(p&&son[p][w]==q)son[p][w]=nq,p=fa[p];
		}
	}last=np;
}*/
void add(int w){
	int p=last;
	int np=newnode(len[p]+1);
	while(p&&!son[p][w])son[p][w]=np,p=fa[p];
	if(!p)fa[np]=1;
	else{
		int q=son[p][w];
		if(len[p]+1==len[q])fa[np]=q;
		else{
			int nq=newnode(len[p]+1);
			memcpy(son[nq],son[q],sizeof son[nq]);
			fa[nq]=fa[q];fa[np]=fa[q]=nq;
			while(p&&son[p][w]==q)son[p][w]=nq,p=fa[p];
		}
	}last=np;
}
char s[maxn];
vector<int>G[maxn];
long long ans=0;
void dfs(int u){
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		dfs(v);
		ans-=1LL*len[u]*cnt[u]*cnt[v]*2;
		cnt[u]+=cnt[v];
	}
}
void deb(){
	for(int i=1;i<=tot;i++){
		fprintf(stderr,"id:%d fa:%d\n",i,fa[i]);
		for(int j=0;j<26;j++)if(son[i][j])
			fprintf(stderr,"%d --%c-- %d\n",i,j+'a',son[i][j]);
	}
}
int main(){
	scanf("%s",s);int n=strlen(s);reverse(s,s+n);
	for(int i=0;i<n;i++)add(s[i]-'a');
	
//	deb();
	for(int u=1,i=0;i<n;i++){
		u=son[u][s[i]-'a'];
		cnt[u]=1;
	}
	ans=(long long)(n-1)*n*(n+1)/2;
	
	for(int i=2;i<=tot;i++)
		G[fa[i]].push_back(i);
	dfs(1);
	
	cout<<ans<<endl;
	return 0;
}
