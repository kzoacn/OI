#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=1e6+555;
int n,len,r[201],cnt,cur=1;
char s[maxn];
struct node{
	int val,ans,id;
	node *go[27],*f;
	vector<node*>rp;
	node(){val=ans=0;memset(go,0,sizeof go);f=0;}
}pool[maxn*2],*root=pool,*last=root;
node *newnode(){
	node *x=&pool[cur++];
	x->id=++cnt;
	return x;
}
void add(int w){
	node *p=last;
	node *np=newnode();np->val=p->val+1;
	while(p&&!p->go[w])p->go[w]=np,p=p->f;
	if(!p)np->f=root;
	else{
		node *q=p->go[w];
		if(p->val+1==q->val)np->f=q;
		else{
			node *nq=newnode();nq->val=p->val+1;
			for(int i=0;i<27;i++)nq->go[i]=q->go[i];
			nq->f=q->f;
			q->f=np->f=nq;
			while(p&&p->go[w]==q)p->go[w]=nq,p=p->f;
		}
	}last=np;
}
vector<node*>vec;
bool cmp(node *a,node *b){return a->val>b->val;}
int Q(const char *s,int l,int r){
	node *u=root;
	for(int i=l;i<r;i++){
		int v=s[i]-'a';
		u=u->go[v];
	}return u->ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s+len);
		for(int j=len,l=strlen(s+len);j<l+len;j++)
			add(s[j]-'a');
		add(26);
		len+=strlen(s+len);
		s[len++]=26+'a';r[i]=len;
	}
	node *u=root;
 	for(int i=0;i<len;i++)
		u=u->go[s[i]-'a'],u->ans=1;
	for(int i=0;i<cnt;i++)vec.push_back(pool+i);
	sort(vec.begin(),vec.end(),cmp);
	for(int i=0;i<vec.size();i++)if(vec[i]->f)
	vec[i]->f->ans+=vec[i]->ans;
	for(int i=1;i<=n;i++)
		printf("%d\n",Q(s,r[i-1],r[i]-1));
	return 0;
}
