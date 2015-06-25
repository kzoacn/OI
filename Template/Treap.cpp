#include<bits/stdc++.h>
using namespace std;
struct Treap{
	struct node{
		int val,key,size,s;
		node *c[2];
		node(int _val=0,node *C=0){
			val=_val;key=rand();
			size=s=1;c[0]=c[1]=C;
		}void rz(){
			size=c[0]->size+s+c[1]->size;
		}
	}*root,*Null;
	Treap(){
		Null=new node(0,0);
		Null->size=Null->s=0;Null->key=INT_MAX;
		Null->c[0]=Null->c[1]=Null;root=Null;
	}
	void rot(node *&t,bool d){
		node *p=t->c[d];t->c[d]=p->c[!d];
		p->c[!d]=t;t->rz();p->rz();t=p;
	}
	void _insert(node *&t,int x){
		if(t==Null){t=new node(x,Null);return;}
		if(t->val==x){t->s++;t->size++;return;}
		_insert(t->c[x>t->val],x);
		if(t->c[x>t->val]->key<t->key)
		rot(t,x>t->val);else t->rz();
	}
	void _del(node *&t,int x){
		if(t->val==x){
			if(t->s>1){t->s--;t->size--;return;}
			bool d=t->c[0]->key>t->c[1]->key;
			if(t->c[d]==Null){delete t;t=Null;return;}	
			rot(t,d);_del(t->c[!d],x);
		}else _del(t->c[x>t->val],x);t->rz();
	}
	int _kth(node *t,int x){
		int r=t->c[0]->size;
		if(x<=r)return _kth(t->c[0],x);
		else if(x>r+t->s) return _kth(t->c[1],x-r-t->s);
		return t->val;
	}
	int _rank(node *t,int x){
		int r=t->c[0]->size;
		if(x<t->val)return _rank(t->c[0],x);
		else if(x>t->val)return _rank(t->c[1],x)+r+t->s;
		return r;
	}
	int _prev(node *t,int x){
		if(t==Null)return INT_MIN;
		if(x<=t->val)return _prev(t->c[0],x);
		return max(t->val,_prev(t->c[1],x));
	}
	int _next(node *t,int x){
		if(t==Null)return INT_MAX;
		if(x>=t->val)return _next(t->c[1],x);
		return min(t->val,_next(t->c[0],x));
	}
	void insert(int x){_insert(root,x);}
	void del(int x){_del(root,x);}
	int kth(int x){return _kth(root,x);}
	int rank(int x){return _rank(root,x);}
	int prev(int x){return _prev(root,x);}
	int next(int x){return _next(root,x);}
}T;
int main(){  
    srand(12121);  
    int n,m;  
    scanf("%d",&n);m=n;  
    while(n--){  
        int opt,x;  
        scanf("%d",&opt);  
        switch(opt){  
            case 1:  
                scanf("%d",&x);  
                T.insert(x);  
                break;  
            case 2:  
                scanf("%d",&x);  
                T.del(x);  
                break;  
            case 3:  
                scanf("%d",&x);  
                printf("%d\n",T.rank(x)+1);  
                break;  
            case 4:               
                scanf("%d",&x);  
                printf("%d\n",T.kth(x));  
                break;  
            case 5:  
                scanf("%d",&x);  
                printf("%d\n",T.prev(x));  
                break;  
            case 6:  
                scanf("%d",&x);  
                printf("%d\n",T.next(x));  
                break;    
        }  
    }  
    return 0;  
}  
