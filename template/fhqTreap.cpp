#include<ctime>
#include<cctype>
#include<cstdio>
#include<cstdlib>
#include<climits>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
int getint(){
	int res=0,f=1;
	char ch,ok=0;
	while(1){
		ch=getchar();
		if(isdigit(ch)){
			res*=10;res+=ch-'0';ok=1;
		}else if(ch=='-')f=-1;
		else if(ok)break;
	}return res*f;
}
void putint(int x){
	printf("%d\n",x);
}
int rnd(){
	static int KEY=12345678;
	return KEY+=KEY<<2|1;
}
struct node;
node *root,*Null;
int tot;
queue<node*>qnode;
const int maxn=1e6+10;
struct node{
	node *c[2];
	int key,rev,val,sum,ls,rs,ss,size,lzy;
	node(int _val=0,node *C=0){
		ls=rs=ss=sum=val=_val;lzy=INT_MIN;
		key=rnd();c[0]=c[1]=C;
		size=1;rev=0;
	}
	void Rev(){
		if(this==Null)return ;
		rev^=1;
		swap(c[0],c[1]);
		swap(ls,rs);
	}
	node* rz(){
//		if(this==NULL)return this;
		
		size=c[0]->size+1+c[1]->size;
		
		sum=c[0]->sum+val+c[1]->sum;
		
		ls=max(c[0]->ls,c[0]->sum+val+max(0,c[1]->ls));
		rs=max(c[1]->rs,c[1]->sum+val+max(0,c[0]->rs));
		
		ss=max(0,c[0]->rs)+val+max(0,c[1]->ls);
		ss=max(ss,max(c[0]->ss,c[1]->ss));
		return this;
	}
	void pushrev(){
		if(rev){
			c[0]->Rev();c[1]->Rev();rev=0;
		}
	}
	void pushsum(){
		if(lzy!=INT_MIN){
			if(c[0]!=Null){
				c[0]->lzy=c[0]->val=lzy;c[0]->sum=lzy*c[0]->size;
				c[0]->ls=c[0]->rs=c[0]->ss=max(c[0]->sum,c[0]->lzy);
			}			
			if(c[1]!=Null){
				c[1]->lzy=c[1]->val=lzy;c[1]->sum=lzy*c[1]->size;
				c[1]->ls=c[1]->rs=c[1]->ss=max(c[1]->sum,c[1]->lzy);
			}
			lzy=INT_MIN;
		}
	}
	node* pushdown(){
		pushrev();
		pushsum();
		return this;
	}
	void split(int need,node *&p,node *&q);
};
node poor[maxn];
node* newnode(int val=0){
	node *x;
	if(qnode.size())x=qnode.front(),qnode.pop();
	else
	if(tot<maxn){
		x=&poor[tot++];
	}else x=new node(val,Null);	
	x->c[0]=x->c[1]=Null;  
    x->size=1; x->rev=0; x->lzy=INT_MIN;  
    x->val=x->sum=x->ls=x->rs=x->ss=val;  
    x->key=rnd();
	return x; 
}
node* merge(node *p,node *q){
	if(p==Null)return q->rz();
	if(q==Null)return p->rz();
	p->pushdown();q->pushdown();
	if(p->key<q->key){
		p->c[1]=merge(p->c[1],q);
		return p->rz();
	}else{
		q->c[0]=merge(p,q->c[0]);
		return q->rz();
	}
}
void node::split(int need,node *&p,node *&q){
	if(this==Null){p=q=Null;return ;}
	pushdown();
	if(c[0]->size>=need){
		c[0]->split(need,p,q);
		c[0]=Null;rz();
		q=merge(q,this);
	}else{
		c[1]->split(need-c[0]->size-1,p,q);
		c[1]=Null;rz();
		p=merge(this,p);
	}
}
void deb(node *root){
	if(root==Null)return ;
	if(root->c[0]!=Null)deb(root->c[0]);
	printf("val:%d sum:%d size:%d ls:%d rs:%d ss:%d\n",root->val,root->sum,root->size,root->ls,root->rs,root->ss);
	
	if(root->c[1]!=Null)deb(root->c[1]);
}         
void erase(node *root){
	if(root==Null)return ;
	erase(root->c[0]);
	erase(root->c[1]);
	qnode.push(root);
}  
void init(){
	root=newnode();
	Null=newnode();
	Null->key=INT_MAX;Null->lzy=INT_MIN;
	Null->val=Null->ls=Null->rs=Null->ss=INT_MIN;
	Null->size=0;Null->c[0]=Null->c[1]=Null;
	root=Null;
}
void insert(){
	int pos=getint();
	int n=getint();
	node *p,*q,*r,*s;
	root->split(pos,p,q);
	while(n--){
		int x=getint();
		p=merge(p,newnode(x));
	}
	root=merge(p,q);
}
void del(){
	int pos=getint()-1,n=getint();
	node *p,*q,*r,*s;
	root->split(pos,p,q);
	q->split(n,r,s);
	erase(r);
	root=merge(p,s);	
}
void makesame(){
	int pos=getint()-1,tot=getint(),c=getint();
	node *p,*q,*r,*s;
	root->split(pos,p,q);
	q->split(tot,r,s);
	r->val=c;r->sum=c*r->size;
	r->rs=r->ls=r->ss=max(r->sum,c);
	r->lzy=c;r->pushdown();
	root=merge(p,merge(r,s));
}
void rev(){
	int pos=getint()-1,tot=getint();
	node *p,*q,*r,*s;
	root->split(pos,p,q);
	q->split(tot,r,s);
	r->Rev();
	root=merge(p,merge(r,s));	
}
void getsum(){
	int pos=getint()-1,tot=getint();
	node *p,*q,*r,*s;
	root->split(pos,p,q);
	q->split(tot,r,s);
	putint(r->sum);
	root=merge(p,merge(r,s));		
}

int n,m;
int main(){
	init();
	char opt[50];
	n=getint();m=getint();
	for(int i=1;i<=n;i++){
		int x=getint();
		root=merge(root,newnode(x));	
	}		
	while(m--){
//		deb(root);
		scanf("%s",opt);
		if(opt[0]=='I'){
			insert();
		}else
		if(opt[0]=='D'){
			del();
		}else
		if(opt[0]=='M'&&opt[2]=='K'){
			makesame();
		}else
		if(opt[0]=='R'){
			rev();
		}else
		if(opt[0]=='G'){
			getsum();
		}else
		putint(root->ss);
	}
	return 0;
}
