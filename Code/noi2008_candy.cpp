#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> par;
int n,m,T;
int getint(){
	char c=getchar();int res=0,f=1;
	while(!isdigit(c))f=f==-1||c=='-'?-1:1,c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
par get(int l,int d,int t){
	t=(t%(2*n)+2*n)%(2*n);
	int f=1;
	if(d==-1)f=t<l?1:-1,t=(t-2*l+2*n)%(2*n);
	else f=t<(n-l)?1:-1;
	if(l+t<=n)return par(l+t,d*f);
	else return par((2*n-(l+t))%(2*n),d*f);
}
struct cloud{
	int l,r,d;
};
struct Fenwick{
	#define lw(x) (x&-x)
	int fw[2005][2005];
	void updata(int x,int y,int d){
		x++;y++;
		for(int i=x;i<2005;i+=lw(i))
		for(int j=y;j<2005;j+=lw(j))
		fw[i][j]+=d;
	}
	int get(int x,int y){
		x++;y++;int ans=0;
		for(int i=x;i;i-=lw(i))
		for(int j=y;j;j-=lw(j))
		ans+=fw[i][j];
		return ans;
	}
	int Qsum(int l,int r,int y){
		l++;r++;y++;
		int all=get(r,2000)-get(l-1,2000);
		return all-(get(r,y-1)-get(l-1,y-1));
	}
}Tr[2];
cloud zero[1000001];
void insert(cloud c){Tr[c.d==1].updata(c.l,c.r,1);}
void del(cloud c){Tr[c.d==1].updata(c.l,c.r,-1);}
int lowerbound(int l,int r,int d,int x){
	while(l<r){
		int mid=(l+r)/2;
		if(get(mid,d,T)>=x)
			d==1?r=mid:l=mid+1;
		else d==1?l=mid+1:r=mid;
	}return l;
}
int upperbound(int l,int r,int d,int x){
	while(l<r){
		int mid=(l+r)/2;
		if(get(mid,d,T)>x)
			d==1?r=mid:l=mid+1;
		else d==1?l=mid+1:r=mid;
	}return l;
}
bool cmp(int x,int y,int d){
	if(d==1)return x<y;
	return x>y;
}
int findm(int l,int r,int d){
	int l=0,r=n;
	while(r-l>2){
		int mid1=l+(r-l)/3,mid2=r-(r-l)/3;
		if(cmp(get(mid1,1,T).first,get(mid2,1,T).first,d))
			r=mid2;
		else l=mid1;
	}int pos=r;
	for(int i=l;i<r;i++)if(cmp(get(i,1,T).first,get(pos,1,T).first,d))
	pos=i;
	return pos;
}
int Q(int lef,int rig){
	int ans=0;
	int pos=findm(0,n,1);
	// [0,pos] inc , [pos+1,n] dec
	l=lowerbound(0,pos+1,lef);
	r=upperbound(0,pos+1,rig);
	ans+=Tr[1].Qsum(0,l-1,lef);
	ans+=Tr[1].Qsum(l,r-1,0);
	l=lowerbound(pos+1,n+1,lef);
	
	return ans;
}
int main(){
	m=getint();n=getint();
	while(m--){
		int op=getint();
		if(op==1){
			T=getint();int C=getint();
			int l=getint(),r=getint(),d=getint();
			zero[C].l=l;zero[C].r=r;zero[C].d=d;
			par tmp=get(l,d,-T);
			zero[C].r=tmp.first+(r-l+1);
			zero[C].l=tmp.first;
			zero[C].d=tmp.second;
			insert(zero[C]);
		}else
		if(op==2){
			T=getint();
			int l=getint(),r=getint();
			printf("%d\n",Q(l,r));
		}else{
			T=getint();
			del(zero[getint()]);
		}
	}
	return 0;
}
