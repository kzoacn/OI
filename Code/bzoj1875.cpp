#include<cstdio>
#include<locale>
#include<climits>
#include<algorithm>
using namespace std;
const int maxn=1e5+5;
int getint(){
	int res=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
struct node{
	int key,val,mn,rev,size;
	int add;
	node *rz(){
		mn=val;size=1;
		if(c[0])mn=min(mn,c[0]->mn),size+=c[0]->size;
		if(c[1])mn=min(mn,c[1]->mn),size+=c[1]->size;
		return this;
	}
	void Rev(){rev^=1;swap(c[0],c[1]);}
	void Add(int x){add+=x;val+=x;mn+=x;}
	void pd(){
		if(c[0]){
			if(rev)c[0]->Rev();
			if(add)c[0]->Add(add);
			rev=add=0;
		}
		if(c[1]){
			if(rev)c[1]->Rev();
			if(add)c[1]->Add(add);
			rev=add=0;
		}
	}
}*root;
int n,m;
node *merge(node *p,node *q){
	if(!p||!q)return p?p->rz():(q?q->rz():0);
	p->pd();q->pd();
	if(p->key<q->key){
		p->c[1]=merge(p->c[1],q);
		return p->rz();
	}else{
		q->c[0]=merge(p,q->c[0]);
		return q->rz();
	}
}
void node::split(int ned,node *&p,node *&q){
	if(!ned){p=q=0;return;}pd();
	if(c[0]&&c[0]->size>=ned){
		c[0]->split(ned,p,q);
		c[0]=0;rz();
		q=merge(q,this);
	}else{
		if(c[1])c[1]->split(ned-(c[0]?c[0]->size:0)-1,p,q);
		else p=q=0;
		c[1]=0;rz();
		p=merge(this,p);
	}
}
int main(){
	n=getint();
	for(int i=1;i<=n;i++){
		int x=getint();
		root=merge(root,new node(x));
	}m=getint();
	while(m--){
		char op[5];scanf("%s",op);
		if(op[0]=='A'){
		
		}else if(op[0]=='I'){
		
		}else if(op[0]=='D'){
		
		}else if(op[0]=='M'){
		
		}else if(op[3]=='E'){
		
		}else{
			
		}
	}
	return 0;
}
