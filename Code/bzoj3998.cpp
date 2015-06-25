#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int son[maxn][26],tot=1,root=1,last=1,val[maxn],fa[maxn],num[maxn],f[maxn];
int newnode(int x){
	val[++tot]=x;
	return tot;
}
int n,ty,K;
void add(int w){
	int p=last;
	int np=newnode(val[p]+1);num[np]=1;
	while(p&&!son[p][w])son[p][w]=np,p=fa[p];
	if(!p)fa[np]=root;
	else{
		int q=son[p][w];
		if(val[p]+1==val[q])fa[np]=q;
		else{
			int nq=newnode(val[p]+1);if(ty==0)num[nq]=1;
			memcpy(son[nq],son[q],sizeof son[nq]);
			fa[nq]=fa[q];fa[np]=fa[q]=nq;
			while(p&&son[p][w]==q)son[p][w]=nq,p=fa[p];
		}
	}last=np;
}
void deb(){
	for(int i=1;i<=tot;i++){
		fprintf(stderr,"id:%d fa:%d\n",i,fa[i]);
		for(int j=0;j<26;j++)if(son[i][j])
			fprintf(stderr,"%d--%c--%d\n",i,j+'a',son[i][j]);
	}
}
char s[maxn];
bool cmp(int x,int y){return val[x]>val[y];}
int main(){
	scanf("%s",s);n=strlen(s);
	scanf("%d%d",&ty,&K);
	for(int i=0;i<n;i++)add(s[i]-'a');
	
//	deb();
	
	static int a[maxn];
	for(int i=1;i<=tot;i++)a[i]=i;
	sort(a+1,a+1+tot,cmp);
	if(ty)for(int i=1;i<tot;i++)num[fa[a[i]]]+=num[a[i]];num[1]=0;
	for(int i=1;i<=tot;i++){
		int u=a[i];
		f[u]=num[u];
		for(int j=0;j<26;j++)if(son[u][j])
			f[u]+=f[son[u][j]];
	}
	string anss;
	int u=1;
	while(num[u]<K){
		K-=num[u];
		for(int i=0;i<26;i++)if(son[u][i]){
			int v=son[u][i];
			if(f[v]<K)K-=f[v];
			else {anss.push_back(i+'a');u=v;break;}
		}
	}//printf("%s",anss.c_str());
	cout<<anss<<endl;
	return 0;
}
