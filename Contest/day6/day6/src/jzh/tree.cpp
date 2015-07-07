#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 50500;
const int M = 150000;
const int inf = 123456789;
int n,m;
int point[N],to[M],next[M],cc=0;
int tot[N],fa[N],top[N],depth[N],biao[N],yuan[N];
struct Info
{
	int len;
	int val;
};
struct InfoX
{
	Info a,b,c,d;
	Info ab,ac,ad,bc,bd,cd;
	Info maxz;
};
struct node
{
	node *lson,*rson;
	int l,r,mid;
	InfoX now,all;
	int lan;
}tree[M];
int getint()
{
	int res=0;
	char ch=getchar();
	while(ch<'0' || ch>'9')
		ch=getchar();
	while('0'<=ch && ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res;
}
int getopt()
{
	char ch=getchar();
	if(ch!='C' && ch!='Q')
		ch=getchar();
	if(ch=='C')
	{
		ch=getchar();
		if(ch=='o')
			return 1;
		else if(ch=='V')
			return 2;
		else
			return 3;
	}
	else
	{
		ch=getchar();
		if(ch=='M')
			return 4;
		else
			return 5;
	}
}
void AddEdge(int x,int y)
{
	cc++;
	next[cc]=point[x];
	point[x]=cc;
	to[cc]=y;
}
void MakeFa(int x)
{
	depth[x]=depth[fa[x]]+1;
	tot[x]=1;
	int now=point[x];
	while(now)
	{
		if(to[now]!=fa[x])
		{
			fa[to[now]]=x;
			MakeFa(to[now]);
			tot[x]+=tot[to[now]];
		}
		now=next[now];
	}
}
void MakeLian(int x,int y,int grand)
{
	top[x]=grand;
	biao[x]=y;
	yuan[y]=x;
	y++;
	int now=point[x];
	int prefer=0;
	while(now)
	{
		if(to[now]!=fa[x])
		{
			if(tot[to[now]]>tot[prefer])
				prefer=to[now];
		}
		now=next[now];
	}
	if(!prefer)
		return;
	MakeLian(prefer,y,grand);
	y+=tot[prefer];
	now=point[x];
	while(now)
	{
		if(to[now]!=fa[x])
		{
			if(to[now]!=prefer)
			{
				MakeLian(to[now],y,to[now]);
				y+=tot[to[now]];
			}
		}
		now=next[now];
	}
}
Info jia(Info x,Info y)
{
	Info res;
	res.len=x.len+y.len;
	res.val=x.val+y.val;
	if(res.val<-inf)
		res.val=-inf;
	return res;
}
Info da(Info x,Info y)
{
	if(x.val>y.val)
		return x;
	if(x.val<y.val)
		return y;
	if(x.len<y.len)
		return y;
	return x;
}
InfoX Combine(InfoX x,InfoX y)
{
	InfoX res;
	res.a=da(x.a,da(jia(x.ab,y.a),jia(x.ad,y.c)));
	res.b=da(y.b,da(jia(y.ab,x.b),jia(y.bc,x.d)));
	res.c=da(x.c,da(jia(x.bc,y.a),jia(x.cd,y.c)));
	res.d=da(y.d,da(jia(y.ad,x.b),jia(y.cd,x.d)));
	res.ab=da(jia(x.ab,y.ab),jia(x.ad,y.bc));
	res.ad=da(jia(x.ad,y.cd),jia(x.ab,y.ad));
	res.bc=da(jia(x.bc,y.ab),jia(x.cd,y.bc));
	res.cd=da(jia(x.cd,y.cd),jia(x.bc,y.ad));
	res.ac=da(x.ac,jia(jia(x.ab,x.cd),y.ac));
	res.bd=da(y.bd,jia(jia(y.ab,y.cd),x.bd));
	res.maxz=da(da(x.maxz,y.maxz),da(jia(x.b,y.a),jia(x.d,y.c)));
	return res;
}
void Replace(node *x)
{
	x->now=Combine(x->lson->now,x->rson->now);
	x->all=Combine(x->lson->all,x->rson->all);
}
void ChangeXX(InfoX &x,int y,int z)
{
	if(y==0)
	{
		x.ab.val=z;
		x.ab.len=1;
	}
	else
	{
		x.cd.val=z;
		x.cd.len=1;
	}
	x.ac=x.ad=x.bc=x.bd=jia(x.ab,x.cd);
	x.a=x.b=da(x.ab,x.ac);
	x.c=x.d=da(x.cd,x.ac);
	x.maxz=da(da(x.ab,x.cd),x.ac);
}
void ChangeX(node *x,int ceng,int val)
{
	ChangeXX(x->all,ceng,val);
	if(ceng==0 && x->now.a.val>=0)
		ChangeXX(x->now,ceng,val);
	if(ceng==1 && x->now.c.val>=0)
		ChangeXX(x->now,ceng,val);
}
void MakeTree(int x,int l,int r)
{
	tree[x].l=l;
	tree[x].r=r;
	tree[x].lan=-1;
	if(l<r)
	{
		tree[x].mid=(l+r)/2;
		tree[x].lson=tree+(x*2);
		tree[x].rson=tree+(x*2+1);
		MakeTree(x*2,l,tree[x].mid);
		MakeTree(x*2+1,tree[x].mid+1,r);
		Replace(tree+x);
	}
	else
	{
		ChangeX(tree+x,0,1);
		ChangeX(tree+x,1,1);
	}
}
void GetData()
{
	int i;
	n=getint();
	for(i=1;i<n;i++)
	{
		int a=getint();
		int b=getint();
		AddEdge(a,b);
		AddEdge(b,a);
	}
	MakeFa(1);
	MakeLian(1,1,1);
	MakeTree(1,1,n);
}
void MakeItX(node *x,int y,int z)
{
	if(z==0)
	{
		if(y==0)
			ChangeXX(x->now,y,x->all.ab.val);
		else
			ChangeXX(x->now,y,x->all.cd.val);
	}
	else
		ChangeXX(x->now,y,-inf);
}
void MakeX(node *x,int y)
{
	if(y==0)
		x->now=x->all;
	else
	{
		ChangeXX(x->now,0,-inf);
		ChangeXX(x->now,1,-inf);
	}
	x->lan=y;
}
void Clear(node *x)
{
	if(x->lan!=-1)
	{
		MakeX(x->lson,x->lan);
		MakeX(x->rson,x->lan);
		x->lan=-1;
	}
}
void Make(node *x,int l,int r,int z)
{
	if(x->l==l && x->r==r)
	{
		MakeX(x,z);
		return;
	}
	Clear(x);
	if(r<=x->mid)
		Make(x->lson,l,r,z);
	else if(l>x->mid)
		Make(x->rson,l,r,z);
	else
	{
		Make(x->lson,l,x->mid,z);
		Make(x->rson,x->mid+1,r,z);
	}
	Replace(x);
}
void ChangeColor(int x,int y,int z)
{
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])
		{
			Make(tree+1,biao[top[y]],biao[y],z);
			y=fa[top[y]];
		}
		else
		{
			Make(tree+1,biao[top[x]],biao[x],z);
			x=fa[top[x]];
		}
	}
	if(biao[x]>biao[y])
		swap(x,y);
	Make(tree+1,biao[x],biao[y],z);
}
void Change(node *x,int wei,int c,int z)
{
	if(x->l==x->r)
	{
		ChangeX(x,c,z);
		return;
	}
	Clear(x);
	if(wei<=x->mid)
		Change(x->lson,wei,c,z);
	else
		Change(x->rson,wei,c,z);
	Replace(x);
}
void MakeIt(node *x,int wei,int c,int z)
{
	if(x->l==x->r)
	{
		MakeItX(x,c,z);
		return;
	}
	Clear(x);
	if(wei<=x->mid)
		MakeIt(x->lson,wei,c,z);
	else
		MakeIt(x->rson,wei,c,z);
	Replace(x);
}
InfoX GetInfo(node *x,int l,int r)
{
	if(x->l==l && x->r==r)
		return x->now;
	Clear(x);
	if(r<=x->mid)
		return GetInfo(x->lson,l,r);
	else if(l>x->mid)
		return GetInfo(x->rson,l,r);
	else
		return Combine(GetInfo(x->lson,l,x->mid),GetInfo(x->rson,x->mid+1,r));
}
InfoX RouteInfo(int x,int y)
{
	InfoX a,b;
	bool ha=0,hb=0;
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])
		{
			if(!hb)
			{
				b=GetInfo(tree+1,biao[top[y]],biao[y]);
				hb=1;
			}
			else
				b=Combine(GetInfo(tree+1,biao[top[y]],biao[y]),b);
			y=fa[top[y]];
		}
		else
		{
			if(!ha)
			{
				a=GetInfo(tree+1,biao[top[x]],biao[x]);
				ha=1;
			}
			else
				a=Combine(GetInfo(tree+1,biao[top[x]],biao[x]),a);
			x=fa[top[x]];
		}
	}
	if(biao[x]<biao[y])
	{
		if(!hb)
		{
			b=GetInfo(tree+1,biao[x],biao[y]);
			hb=1;
		}
		else
			b=Combine(GetInfo(tree+1,biao[x],biao[y]),b);
	}
	else
	{
		if(!ha)
		{
			a=GetInfo(tree+1,biao[y],biao[x]);
			ha=1;
		}
		else
			a=Combine(GetInfo(tree+1,biao[y],biao[x]),a);
	}
	InfoX c;
	if(!ha)
		c=b;
	else if(!hb)
		c=a;
	else
	{
		swap(a.a,a.b);
		swap(a.c,a.d);
		swap(a.ac,a.bd);
		swap(a.ad,a.bc);
		c=Combine(a,b);
	}
	return c;
}
void GetVal(int x,int y)
{
	InfoX res=RouteInfo(x,y);
	if(res.maxz.val>=0)
		printf("%d\n",res.maxz.val);
	else
		printf("Bad Request\n");
}
void GetLen(int x,int y)
{
	InfoX res=RouteInfo(x,y);
	if(res.maxz.val>=0)
		printf("%d\n",res.maxz.len);
	else
		printf("0\n");
}
void DoIt()
{
	m=getint();
	while(m--)
	{
		int opt=getopt();
		if(opt==1)
		{
			int a=getint();
			int b=getint();
			int c=getint();
			ChangeColor(a,b,c);
		}
		else if(opt==2)
		{
			int a=getint();
			int b=getint();
			int c=getint();
			Change(tree+1,biao[a],b,c);
		}
		else if(opt==3)
		{
			int a=getint();
			int b=getint();
			int c=getint();
			MakeIt(tree+1,biao[a],b,c);
		}
		else if(opt==4)
		{
			int a=getint();
			int b=getint();
			GetVal(a,b);
		}
		else
		{
			int a=getint();
			int b=getint();
			GetLen(a,b);
		}
	}
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	GetData();
	DoIt();
	return 0;
}