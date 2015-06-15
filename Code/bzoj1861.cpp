#include<bits/stdc++.h>
using namespace std;
const int maxn=80010;
struct node{
	int key,id,siz;
	node *rz(){
		siz=1;
		if(c[0])siz+=c[0]->siz,c[0]->f=this;
		if(c[1])siz+=c[1]->siz,c[1]->f=this;
		return this;
	}
	node *c[2],*f;
	void split(int ned,node *&p,node *&q);
}nd[maxn],*root;
node *merge(node *p,node *q){
	if(!p||!q)return (p?p->rz():(q?q->rz():0));
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
	if(c[0]&&c[0]->siz>=ned){
		c[0]->split(ned,p,q);c[0]->f=0;c[0]=0;rz();
		q=merge(q,this);
	}else{
		c[1]->split(ned-sz(c[0])-1,p,q);c[1]->f=0;c[1]=0;rz();
		p=merge(this,p);
	}
}
int rank(node *x){
	int ans=sz(x->c[0]);
	while(x->f){
		if(x->f->c[1]==x)ans+=sz(x->f->c[0])+1;
		x=x->f;
	}return ans+1;
}
int kth(int k){
	node *p,*q,*x,*y;
	root->split(k-1,p,q);
	q->split(1,x,y);
	int ans=x-nd;
	root=merge(p,merge(x,y));
	return ans;
}
void Top(int _x){
	node *x=nd+_x;
	int k=rank(x);
	node *p,*q,*a,*b;
	root->split(k-1,p,q);
	q->split(1,a,b);
	root=merge(a,merge(p,b));
}
void Bottom(int _x){
	node *x=nd+_x;
	int k=rank(x);
	node *p,*q,*a,*b;
	root->split(k-1,p,q);
	q->split(1,a,b);
	root=merge(merge(p,b),a);
}
void Insert(int k){
	node *p,*q,*x,*y,*a,*b;
	root->split(k-1,p,q);
	q->split(1,x,y);
	y->split(1,a,b);
//	swap(x->id,a->id);
	root=merge(merge(p,a),merge(x,b));
}
int n,m;
int in(){
	int r=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r*f;
}
void deb(node *t){
	if(t->c[0])deb(t->c[0]);
	printf("%d ",t->id);
	if(t->c[1])deb(t->c[1]);
}
int main(){
	freopen("bzoj1861.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		int x=in();
		nd[x].id=x;nd[x].key=rand();
		root=merge(root,nd+x);
	}
	while(m--){
//		deb(root);puts("");
		char op[7];scanf("%s",op);	
		int x=in();
		if(op[0]=='T'){
			Top(x);
		}else if(op[0]=='B'){
			Bottom(x);
		}else if(op[0]=='I'){
			int t=in();
			if(t==1)Insert(rank(nd+x));
			if(t==-1)Insert(rank(nd+x)-1);
		}else if(op[0]=='A'){
			printf("%d\n",rank(nd+x)-1);		
		}else if(op[0]=='Q'){
			printf("%d\n",kth(x));
		}
	}	
	return 0;
}
