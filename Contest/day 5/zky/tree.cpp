#include<cstdio>
#include<cstring>
#include<vector>
#include<cctype>
#include<algorithm>
using namespace std;
const int maxn=50010;
int in(){
	int r=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))r=r*10+c-'0',c=getchar();
	return r;
}
int n,m;
struct Ans{
	int ans,len;
	Ans(){ans=len=0;}
	Ans(int ans,int len):ans(ans),len(len){}
	bool operator<(const Ans &o)const{
		return ans==o.ans?ans<o.ans:len<o.len;
	}
};
Ans operator+(const Ans &ls,const Ans &rs){return Ans(ls.ans+rs.ans,ls.len+rs.len);}
void cp(const Ans _d[2][2],Ans d[2][2]){
	d[0][0]=_d[0][0];
	d[0][1]=_d[0][1];
	d[1][0]=_d[1][0];
	d[1][1]=_d[1][1];	
}
struct info{
	int sum,siz,mn[2];
	Ans A,dl[2][2],dr[2][2];
	short l,r,con;
	info(int va[2],int co[2]){
		siz=1;sum=va[0]+va[1];
		mn[0]=va[0];mn[1]=va[1];
		dl[0][0].ans=va[0]*(!co[0]);dl[0][0].len=(!co[0]);
		dl[1][1].ans=va[1]*(!co[1]);dl[1][1].len=(!co[1]);
		if(co[0]==0&&co[1]==0)
			dl[0][1]=dl[1][0]=Ans(va[0]+va[1],2);
		for(int i=0;i<=1;i++)
		for(int j=0;j<=1;j++)
		dr[j][i]=dl[i][j],A=max(A,dl[i][j]);
		l=r=(co[0]<<1)+co[1];
		con=l!=3;
	}
	info(){}
	void flip(){
		if(siz%2==0)swap(mn[0],mn[1]);
		swap(dl,dr);
	}
};
info operator+(const info &ls,const info &rs){
	info I;
	I.sum=ls.sum+rs.sum;I.siz=ls.siz+rs.siz;
	I.l=ls.l;I.r=ls.r;I.con=ls.con&&(ls.r|rs.l)!=3&&rs.con;
	if(ls.siz%2==0){
		I.mn[0]=min(ls.mn[0],rs.mn[0]);
		I.mn[1]=min(ls.mn[1],rs.mn[1]);
	}else{
		I.mn[0]=min(ls.mn[0],rs.mn[1]);
		I.mn[1]=min(ls.mn[1],rs.mn[0]);
	}
	if((ls.r|rs.l)==3){
		I.A=max(ls.A,rs.A);
		cp(ls.dl,I.dl);
		cp(rs.dr,I.dr);
	}else{
		Ans mid;
		if((ls.r|rs.l)==1){
			I.A=max(I.A,max(ls.dr[1][0],ls.dr[1][1])+max(rs.dl[1][0],rs.dl[1][1]));
		}else if((ls.r|rs.l)==2){
			I.A=max(I.A,max(ls.dr[0][0],ls.dr[0][1])+max(rs.dl[0][0],rs.dl[0][1]));
		}else{
			I.A=max(I.A,max(ls.dr[1][0],ls.dr[1][1])+max(rs.dl[1][0],rs.dl[1][1]));
			I.A=max(I.A,max(ls.dr[0][0],ls.dr[0][1])+max(rs.dl[0][0],rs.dl[0][1]));
		}
		if(ls.con){
			for(int i=0;i<=1;i++)for(int j=0;j<=1;j++)
			I.dl[i][j]=max(ls.dl[i][0]+rs.dl[0][j],ls.dl[i][1]+rs.dl[1][j]);			
		}else cp(ls.dl,I.dl);
		
		if(rs.con){
			for(int i=0;i<=1;i++)for(int j=0;j<=1;j++)
			I.dr[i][j]=max(rs.dr[i][0]+ls.dr[0][j],rs.dr[i][1]+ls.dr[1][j]);						
		}else cp(rs.dr,I.dr);


		for(int i=0;i<=1;i++)
		for(int j=0;j<=1;j++)
		I.dl[i][j]=max(I.dl[i][j],ls.dl[i][j]),
		I.dr[i][j]=max(I.dr[i][j],rs.dr[i][j]);

		for(int i=0;i<=1;i++)
		for(int j=0;j<=1;j++)
		I.A=max(I.A,I.dl[i][j]),
		I.A=max(I.A,I.dr[i][j]);	
		
	}
	return I;
}
#define clear(x) memset(x,0,sizeof x)
info operator+(int A,const info &B){
	info I=B;
	if(A){
		I.l=I.r=3;I.con=0;
		I.A=Ans(0,0);
		clear(I.dl);clear(I.dr);
	}else{
		I.l=I.r=0;I.con=1;
		if(I.siz%2==0){
			I.dl[0][0]=I.dl[1][1]=Ans(I.sum,I.siz*2);
			I.dl[0][1]=Ans(I.sum-I.mn[1],I.siz*2-1);
			I.dl[1][0]=Ans(I.sum-I.mn[0],I.siz*2-1);
		}else{
			I.dl[0][1]=I.dl[1][0]=Ans(I.sum,I.siz*2);
			I.dl[0][0]=Ans(I.sum-I.mn[1],I.siz*2-1);
			I.dl[1][1]=Ans(I.sum-I.mn[0],I.siz*2-1);			
		}		
		for(int i=0;i<=1;i++)
		for(int j=0;j<=1;j++)
		I.dr[j][i]=I.dl[i][j],I.A=max(I.A,I.dl[i][j]);
	}return I;
}
struct node{
	int val[2],col[2];
	info I;int laz,rev;
	node *f,*c[2];
	node(){laz=-1;}
	node *rz(){
		I=info(val,col);
		if(c[0])I=c[0]->I+I;
		if(c[1])I=I+c[1]->I;
		return this;
	}
	void mkrv(){
		rev^=1;
		swap(c[0],c[1]);
		I.flip();
	}
	void pd(){
		if(rev){
			if(c[0])c[0]->mkrv();
			if(c[1])c[1]->mkrv();
			rev^=1;
		}
		if(laz==-1)return;
		if(c[0]){
			c[0]->I=laz+c[0]->I,c[0]->laz=laz;
			c[0]->col[0]=c[0]->col[1]=laz;
		}
		if(c[1]){
			c[1]->I=laz+c[1]->I,c[1]->laz=laz;
			c[1]->col[0]=c[1]->col[1]=laz;
		}
		laz=-1;
	}
	bool d(){return f->c[1]==this;}
	bool rt(){return !f||(f->c[0]!=this&&f->c[1]!=this);}
	void sets(node *x,int d){pd();c[d]=x;if(x)x->f=this;rz();}
}nd[maxn];
void rot(node *x){
	node *y=x->f;if(!y->rt())y->f->pd();
	y->pd();x->pd();int d=x->d();
	y->sets(x->c[!d],d);
	if(y->rt())x->f=y->f;
	else y->f->sets(x,y->d());
	x->sets(y,!d);
}
void splay(node *x){
	while(!x->rt()){
		if(x->f->rt())rot(x);
		else if(x->d()==x->f->d())rot(x->f),rot(x);
		else rot(x),rot(x);
	}
}
node* access(node *x){
	node *y=0;
	for(;x;x=x->f){
		splay(x);
		x->sets(y,1);
		y=x;
	}return y;
}
void makert(node *x){
	access(x)->mkrv();
	splay(x);
}
void link(node *x,node *y){
	makert(x);
	x->f=y;
	access(x);
}
void Cover(int u,int v,int c){
	node *x=nd+u,*y=nd+v;
	makert(x);access(y);splay(y);
	y->I=c+y->I;
	y->laz=c;
	y->col[0]=y->col[1]=c;
	y->pd();	
}
void CVal(int id,int la,int va){
	node *x=nd+id;
	makert(x);splay(x);
	x->val[la]=va;x->rz();
}
void CColor(int id,int la,int co){
	node *x=nd+id;
	makert(x);splay(x);
	x->col[la]=co;x->rz();
}
int Q(int u,int v,int ty){
	node *x=nd+u,*y=nd+v;
	makert(x);
	access(y);
	splay(y);
	if(!ty)return y->I.A.len?y->I.A.ans:-1;
	else return y->I.A.len;	
}
namespace BF{
	vector<int>G[maxn];
	int fa[maxn],dep[maxn];
	int val[maxn][2],col[maxn][2];
	void dfs(int u){
		val[u][0]=val[u][1]=1;
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(v==fa[u])continue;
			fa[v]=u;dep[v]=dep[u]+1;
			dfs(v);
		}
	}
	void Cover(int u,int v,int c){
		if(dep[u]<dep[v])swap(u,v);
		while(dep[u]>dep[v])
			col[u][0]=col[u][1]=c,
			u=fa[u];
		while(u!=v){
			col[u][0]=col[u][1]=c,
			u=fa[u];
			col[v][0]=col[v][1]=c,
			v=fa[v];	
		}
			col[v][0]=col[v][1]=c;
	}
	void CVal(int id,int la,int va){
		val[id][la]=va;
	}
	void CColor(int id,int la,int co){
		col[id][la]=co;
	}
	int lca(int u,int v){
		static int vis[maxn],T;
		T++;
		while(u)vis[u]=T,u=fa[u];
		while(v){
			if(vis[v]==T)return v;
			v=fa[v];
		}return v;
	}
	int Q(int u,int v,int ty){
		int LCA=lca(u,v);
		vector<int>way1,way2;
		while(u!=LCA)way1.push_back(u),u=fa[u];
		way1.push_back(u);
		while(v!=LCA)way2.push_back(v),v=fa[v];
		reverse(way2.begin(),way2.end());
		vector<int>way;
		way.push_back(0);
		for(int i=0;i<way1.size();i++)way.push_back(way1[i]);
		for(int i=0;i<way2.size();i++)way.push_back(way2[i]);
		static int f[maxn][2],g[maxn][2];
		int ans=0,len=0;
		if(way.size()==1){return -1;}
		for(int i=1;i<way.size();i++){
			int y=way[i-1],x=way[i];
			if(!col[x][0])f[x][0]=val[x][0],g[x][0]=1;else f[x][0]=g[x][0]=0;
			if(!col[x][1])f[x][1]=val[x][1],g[x][1]=1;else f[x][1]=g[x][1]=0;
		
			if(col[x][0]==0&&col[x][1]==0){
				for(int j=0;j<=1;j++)
				if(f[y][j]>f[y][j^1]+val[x][j^1]){
					f[x][j]+=f[y][j];
					g[x][j]+=g[y][j];
				}else if(f[y][j]<f[y][j^1]+val[x][j^1]){
					f[x][j]+=f[y][j^1]+val[x][j^1];
					g[x][j]+=g[y][j^1]+1;				
				}else{
					f[x][j]+=f[y][j];
					g[x][j]+=max(g[y][j^1]+1,g[y][j]);
				}
			}else if(col[x][0]==1&&col[x][1]==1){
			
			}else {
				int j;
				if(col[x][0]==0)j=0;else j=1;
				f[x][j]+=f[y][j];
				g[x][j]+=g[y][j];
			}
			if(f[x][0]>ans)ans=f[x][0],len=g[x][0];
			if(f[x][1]>ans)ans=f[x][1],len=g[x][1];
			if(f[x][0]==ans&&g[x][0]>len)len=g[x][0];
			if(f[x][1]==ans&&g[x][1]>len)len=g[x][1];
		}
		if(!ty)return len==0?-1:ans;
		else return len;
	}	
	int solve(){
		for(int i=1;i<n;i++){
			int u=in(),v=in();
			G[u].push_back(v);
			G[v].push_back(u);
		}

		dfs(1);
	
		m=in();
	
		while(m--){
			char op[10];scanf("%s",op);
			if(op[0]=='C'){
				if(op[1]=='o'){
					int u=in(),v=in(),c=in();
					Cover(u,v,c);
				}else
				if(op[1]=='V'){
					int id=in(),la=in(),va=in();
					CVal(id,la,va);
				}else{
					int id=in(),la=in(),co=in();
					CColor(id,la,co);			
				}
			}else if(op[0]=='Q'){
				int u=in(),v=in();
				int res=Q(u,v,op[1]=='L');
				if(res==-1)puts("Bad Request.");
				else printf("%d\n",res);		
			}
		}return 0;	
	}
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n=in();
	if(n<=1000)return BF::solve();
	for(int i=1;i<=n;i++)
		nd[i].val[0]=nd[i].val[1]=1,nd[i].rz();
	for(int i=1;i<n;i++){
		int u=in(),v=in();
		link(nd+u,nd+v);
	}

	m=in();
	
	while(m--){
		char op[10];scanf("%s",op);
		if(op[0]=='C'){
			if(op[1]=='o'){
				int u=in(),v=in(),c=in();
				Cover(u,v,c);
			}else
			if(op[1]=='V'){
				int id=in(),la=in(),va=in();
				CVal(id,la,va);
			}else{
				int id=in(),la=in(),co=in();
				CColor(id,la,co);			
			}
		}else if(op[0]=='Q'){
			int u=in(),v=in();
			int res=Q(u,v,op[1]=='L');
			if(res==-1)puts("Bad Request.");
			else printf("%d\n",res);		
		}
	}
	
	return 0;
}
