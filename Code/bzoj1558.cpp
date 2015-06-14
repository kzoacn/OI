#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,m;
struct node{
	int size;
	int lef,ld;
	int rig,rd;
	int lo,ro;
	node(){size=lef=ld=rig=rd=0;lo=0,ro=0;}	
}t[maxn<<2];
node operator+(const node &ls,const node &rs){
	node C;
	C.size=ls.size+rs.size;;
	C.lef=ls.lef;C.ld=ls.ld;
	C.rig=rs.rig;C.rd=rs.rd;
	C.lo=ls.lo;C.ro=rs.ro;
	if(ls.ro&&rs.lo){
		C.size--;
	}else
	if(ls.ro){
		if(rs.lef-rs.ld==ls.rig)C.size--;
	}else
	if(rs.lo){
		if(ls.rig+ls.rd==rs.lef)C.size--;
	}else{
		if(ls.rd==rs.ld&&ls.rig+ls.rd==rs.lef)C.size--;	
	}return C;
}
struct sgt{
	#define lson i<<1,l,(l+r)/2
	#define rson i<<1|1,(l+r)/2+1,r
	#define ls i<<1
	#define rs i<<1|1
	void build(int i,int l,int r){
		if(l==r){
						
		}
	}	
	node Q(int i,int l,int r,int l0,int r0){
	
	}
	void C(int i,int l,int r,int l0,int r0){
	
	}	
};
int main(){
	
	return 0;
}
