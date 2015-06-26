#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int son[maxn][26],*len,fa[maxn],*rigm;//,minl[maxn];
char rigs[maxn];
int last=1,tot=1,root=1;
int newnode(int x){
	len[++tot]=x;
	return tot;
}
void add(int w,int r){
	int p=last;
	int np=newnode(len[p]+1);rigm[np]=r;rigs[np]=1;
	while(p&&!son[p][w])son[p][w]=np,p=fa[p];
	if(!p)fa[np]=1;
	else{
		int q=son[p][w];
		if(len[p]+1==len[q])fa[np]=q;
		else{
			int nq=newnode(len[p]+1);
			memcpy(son[nq],son[q],sizeof son[nq]);
			fa[nq]=fa[q];fa[q]=fa[np]=nq;
			while(p&&son[p][w]==q)son[p][w]=nq,p=fa[p];
		}
	}last=np;
}
void deb(){
	for(int i=1;i<=tot;i++){
		fprintf(stderr,"id:%d fa:%d\n",i,fa[i]);
		for(int j=0;j<26;j++)if(son[i][j]){
			fprintf(stderr,"%d--%c--%d\n",i,j+'a',son[i][j]);
		}
	}
}
char *s;
int n;
bool cmp(int x,int y){return len[x]>len[y];}
pair<int,int> par[int(1e6+1)];
int main(){
	s=new char[maxn];
	rigm=new int[maxn];
	len=new int[maxn];
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++)
		add(s[i]-'a',i);
	delete s;
//	deb();
	
	static int tp[maxn];
	for(int i=1;i<=tot;i++)tp[i]=i;
	sort(tp+1,tp+1+tot,cmp);
	delete len;
	for(int i=1;i<=tot;i++){
		int u=tp[i];
		rigm[fa[u]]=max(rigm[fa[u]],rigm[u]);
		rigs[fa[u]]=0;
	}
	int *minl=fa;
	for(int i=1;i<=tot;i++)minl[i]=tot+1;
	minl[1]=0;reverse(tp+1,tp+1+tot);
	for(int i=1;i<=tot;i++){
		int u=tp[i];
		for(int j=0;j<26;j++)if(son[u][j])
			minl[son[u][j]]=min(minl[son[u][j]],minl[u]+1);
	}
	int *a=tp;
	for(int i=1;i<=n;i++)a[i]=n+1;
	int psz=0;
	for(int i=1;i<=tot;i++)if(rigs[i]==1){
		int ps=rigm[i]-minl[i]+1;
		a[ps]=min(a[ps],minl[i]);
		par[psz++]=make_pair(ps,minl[i]);
		par[psz++]=make_pair(rigm[i]+1,-minl[i]);
//		b[ps].push_back(minl[i]);
//		b[rigm[i]+1].push_back(-minl[i]);
	}sort(par,par+psz);
	int cur=a[n];
	static int anss[maxn/2];
	for(int i=n;i>=1;i--){
		cur=min(cur,a[i]);
		anss[i]=cur;
		cur++;
	}
	delete rigm;
	multiset<int>S;
	cur=0;
	for(int i=1;i<=n;i++){
		while(par[cur].first==i){
			int x=par[cur].second;
			if(x<0)S.erase(S.find(-x));
			else S.insert(x);
			cur++;
		}
		if(!S.empty())
		anss[i]=min(anss[i],*S.begin());
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",anss[i]);
	return 0;
}
