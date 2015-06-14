#include<bits/stdc++.h>
using namespace std;
int rnd(){
	static int x=12345679;
	return x+=x<<2|1;
}
struct node{
	int key,val,mx,size;
	node(int _val=0,node *C=0){
		key=rnd();
		val=_val;
		mx=_val;
		size=1;
		c[0]=c[1]=C;
	}
	node *c[2];
	node* rz(){
		size=c[0]->size+1+c[1]->size;
		mx=val;mx=max(mx,c[0]->mx);mx=max(mx,c[1]->mx);
		return this;
	}
	void split(int ned,node *&p,node *&q);
}*root,*null,pool[int(1e5)+5],*cur=pool;
node *newnode(int _val,node *C){
	node *x=cur++;
	*x=node(_val,C);
	return x;
}
node *merge(node *p,node *q){
	if(p==null)return q->rz();
	if(q==null)return p->rz();
	if(p->val<q->val){
		p->c[1]=merge(p->c[1],q);
		return p->rz();
	}else{
		q->c[0]=merge(p,q->c[0]);
		return q->rz();
	}
}
void node::split(int ned,node *&p,node *&q){
	if(this==null){p=null;q=null;return;}	
	if(c[0]->size>=ned){
		c[0]->split(ned,p,q);
		c[0]=null;rz();
		q=merge(q,this);
	}else{
		c[1]->split(ned-c[0]->size-1,p,q);
		c[1]=null;rz();
		p=merge(this,p);
	}
}
int main(){
	null=newnode(0,0);null->c[0]=null->c[1]=null;null->size=0;null->key=INT_MAX;
	root=null;int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		int x;
		scanf("%d",&x);
		node *p,*q;
		root->split(x,p,q);
		p=merge(p,newnode(p->mx+1,null));
		root=merge(p,q);
		printf("%d\n",root->mx);
	}
	return 0;
}
