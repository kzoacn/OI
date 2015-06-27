#include<bits/stdc++.h>
using namespace std;
const int maxn=200005;
int tot=1,last=1,root=1;
int son[maxn][26],fa[maxn],len[maxn],f[maxn];
int newnode(int x){
	len[++tot]=x;
	return tot;
}
void add(int w){
	int p=last;
	if(son[p][w]){
		int q=son[p][w];f[q]++;
		if(len[p]+1==len[q])last=q;
		else{
			int nq=newnode(len[p]+1);
			memcpy(son[nq],son[q],sizeof son[nq]);
			fa[nq]=fa[q];
			fa[q]=nq;
			while(p&&son[p][w]==q)son[p][w]=nq,p=fa[p];
			last=nq;
		}
	}else{
		int np=newnode(len[p]+1);f[np]++;
		while(p&&!son[p][w])son[p][w]=np,p=fa[p];
		if(!p)fa[np]=1;
		else{
			int q=son[p][w];
			if(len[p]+1==len[q])fa[np]=q;
			else{
				int nq=newnode(len[p]+1);
				memcpy(son[nq],son[q],sizeof son[nq]);
				fa[nq]=fa[q];
				fa[q]=fa[np]=nq;
				while(p&&son[p][w]==q)son[p][w]=nq,p=fa[p];
			}
		}last=np;
	}
}
bool cmp(int x,int y){return len[x]>len[y];}
char s[maxn];
int n,q;
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		int l=strlen(s);
		for(int j=0;j<l;j++)
			add(s[j]-'a');
		last=root;
	}
	static int tp[maxn];
	for(int i=1;i<=tot;i++)tp[i]=i;
	sort(tp+1,tp+1+tot,cmp);
	for(int i=1;i<=tot;i++)f[fa[tp[i]]]+=f[tp[i]];
	while(q--){
		scanf("%s",s);
		int l=strlen(s);
		int u=1;
		for(int i=0;i<l;i++)u=son[u][s[i]-'a'];
		printf("%d\n",f[u]);
	}
	return 0;
}
