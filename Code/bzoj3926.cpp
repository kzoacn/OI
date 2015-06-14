#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1e5+5;
int n,C,c[maxn],in[maxn],mp[maxn];
vector<int>G[maxn];
LL ans=0;
struct node{
	int val;
	node *go[20],*f;
}pool[maxn*20],*cur=pool,*root;
node *la[maxn*20];
node* newnode(){
	node *x=cur++;
	return x;
}
node* add(node *last,int w){
	node *p=last;
	if(p->go[w]&&p->val+1==p->go[w]->val)return p->go[w];
	node *np=newnode();
	np->val=p->val+1;
	while(p&&!p->go[w])p->go[w]=np,p=p->f;
	if(!p)np->f=root;
	else{
		node *q=p->go[w];
		if(p->val+1==q->val)np->f=q;
		else{
			node *nq=newnode();nq->val=p->val+1;
			memcpy(nq->go,q->go,sizeof(q->go));
			nq->f=q->f;
			q->f=np->f=nq;
			while(p&&p->go[w]==q)p->go[w]=nq,p=p->f;
		}
	}return np;
}
void dfs(int u,int fa){
	la[u]=add(la[fa],c[u]);
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==fa)continue;
		dfs(v,u);
	}
}
int vis[maxn*20];
void dfs(node *u){
	if(vis[u-pool])return;
	vis[u-pool]=1;if(u->f)ans+=u->val-u->f->val;
	for(int i=0;i<C;i++)if(u->go[i])
		dfs(u->go[i]);
}
int main(){
	root=newnode();
	scanf("%d%d",&n,&C);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
		in[u]++;in[v]++;
	}la[0]=root;
	for(int i=1;i<=n;i++)if(in[i]==1)
		dfs(i,0);
	dfs(root);
	cout<<ans<<endl;
	return 0;
}
