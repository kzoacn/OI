#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int in(){
	int r=0,f=1;char c=getchar();
	while(!isdigit(c))f=c=='-'?-1:f,c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r*f;
}
int n,m;
struct info{
	int siz;
	LL sum;
	info(){siz=1;sum=0;}
	info(int siz,LL sum):siz(siz),sum(sum){};
};
struct flag{
	LL mul,a,d;
	flag(){mul=1;a=d=0;}
	flag(LL m,LL a,LL d):mul(m),a(a),d(d){}
	void cl(){mul=1;a=d=0;}
	bool em(){return mul==1&&a==0&&d==0;}
};
info operator+(const info &A,const info &B){return info(A.siz+B.siz,A.sum+B.sum);}
flag operator+(const flag &A,const flag &B){
	return flag(A.mul*B.mul,B.a*A.mul+A.a,B.d*A.mul+A.d);
}
info operator+(const flag &A,const info &B){
	return info(B.siz,B.sum*A.mul+B.siz*A.a+A.d*B.siz*(B.siz-1)/2);
}
LL operator+(flag A,LL B){
	return B*A.mul+A.a;
}
struct node{
	LL val;
	info I;
	flag F;
	node *c[2],*f;
	void split(int ned,node *&p,node *&q);
	node* rz(){
		I.siz=1;I.siz=val;
		if(c[0])I=c[0]->I+I;
		if(c[1])I=c[1]->I+I;
	}
	void pd(){
		if(!F.em()){
			if(c[0]){
				c[0]->F=F+c[0]->F;
				c[0]->I=F+c[0]->I;
				c[0]->val=F+c[0]->val;
			}
			if(c[1]){
				
				c[1]->F=F+c[0]->F;
				c[1]->I=F+c[0]->I;
				c[1]->val=F+c[0]->val;				
			}
			F.cl();
		}
	}
};
node *merge(node *p,node *q){
	
}
void node::split(int ned,node *&p,node *&q){
	
}
int main(){
	n=in();m=in();
	
	return 0;
}
