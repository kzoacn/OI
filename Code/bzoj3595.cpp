#include<bits/stdc++.h>
using namespace std;
const int maxn=300010;
struct node{
	int key,val,siz;
	node *c[2],*f;
	node(){}
	node *rz(){siz=1;if(c[0])siz+=c[0]->siz,c[0]->f=this;if(c[1])siz+=c[1]->siz,c[1]->f=this;return this;}
	void split(int ned,node *&p,node *&q);
}nd[maxn],*root;
void deb(node *t);
map<int,int>mp;
int rmp[maxn];
node* merge(node *p,node *q){
	if(!p||!q)return p?p->rz():(q?q->rz():0);
	if(p->key<q->key){
		p->c[1]=merge(p->c[1],q);
		return p->rz();
	}else{
		q->c[0]=merge(p,q->c[0]);
		return q->rz();
	}
}
#define sz(x) (x?x->siz:0)
void node::split(int ned,node *&p,node *&q){
	if(!ned){p=0;q=this;return;}
	if(ned==siz){p=this;q=0;return;}
	if(sz(c[0])>=ned){
		c[0]->split(ned,p,q);
		c[0]->f=0;c[0]=0;rz();
		q=merge(q,this);
	}else{
		c[1]->split(ned-sz(c[0])-1,p,q);
		c[1]->f=0;c[1]=0;rz();
		p=merge(this,p);
	}
}
int rank(int _x){
	node *x=nd+_x;
	int ans=sz(x->c[0]);
	while(x->f){
		if(x==x->f->c[1])ans+=sz(x->f->c[0])+1;
		x=x->f;
	}
	return ans+1;
}
int Top(int x){
	int ans=rank(x);
	node *p,*q,*r,*s;
	root->split(ans-1,p,q);
	q->split(1,r,s);
	root=merge(r,merge(p,s));
	return ans;
}
int Last(int x){
	int ans=rank(x);
	node *p,*q,*r,*s;
	root->split(ans-1,p,q);
//	deb(p);puts("");
//	deb(q);puts("");
	q->split(1,r,s);
//	deb(r);puts("");
//	deb(s);puts("");
	root=merge(merge(p,s),r);
//	deb(root);puts("");
	return ans;
}
int Kth(int k){
	node *x=root;
	while(x){
		if(sz(x->c[0])>=k)
			x=x->c[0];
		else if(sz(x->c[0])+1==k)break;
		else k-=sz(x->c[0])+1,x=x->c[1];
	}return rmp[x-nd];
}
#define id(x) (x?x-nd:0)
void deb(node *t){
	if(t->c[0])deb(t->c[0]);
	printf("id:%d f:%d c[0]:%d c[1]:%d\n",id(t),id(t->f),id(t->c[0]),id(t->c[1]));
	if(t->c[1])deb(t->c[1]);
}
int n,m;
int main(){
//	freopen("bzoj3595.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)mp[i]=i,rmp[i]=i;
	for(int i=1;i<=n;i++){
		nd[i].key=rand();
		root=merge(root,nd+i);
	}
	
	
	int lans=0;
	while(m--){
//		deb(root);
		int ty;scanf("%d",&ty);
		if(ty==1){
			int x,y;scanf("%d%d",&x,&y);x-=lans;y-=lans;
			printf("%d\n",lans=rank(x));
			mp[y]=mp[x];rmp[mp[x]]=y;
		}else if(ty==2){
			int x;scanf("%d",&x);x-=lans;
			x=mp[x];
			printf("%d\n",lans=Top(x));
		}else if(ty==3){
			int x;scanf("%d",&x);x-=lans;
			x=mp[x];
			printf("%d\n",lans=Last(x));
		}else{
			int x;scanf("%d",&x);x-=lans;
			printf("%d\n",lans=Kth(x));
		}
		
		
		lans=0;
	}
	return 0;
}
