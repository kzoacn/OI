#include<bits/stdc++.h>
using namespace std;
struct node{
	node *x;
	long long a[1024];
};
node *x;
int main(){
	x=new node();
	while(1){
		x->x=new node();
		x=x->x;
	}
}
