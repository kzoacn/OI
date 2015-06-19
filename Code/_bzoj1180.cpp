#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define M 30300
using namespace std;
struct abcd{
	abcd *fa,*ls,*rs;
	int num,sum;
	bool rev_mark;
	abcd(int x);
	void Push_Up();
	void Push_Down();
	void Reverse();
}*null=new abcd(0),*tree[M];
abcd :: abcd(int x)
{
	fa=ls=rs=null;
	num=sum=x;
	rev_mark=0;
}
void abcd :: Push_Up()
{
	sum=ls->sum+rs->sum+num;
}
void abcd :: Push_Down()
{
	if(fa->ls==this||fa->rs==this)
		fa->Push_Down();
	if(rev_mark)
	{
		ls->Reverse();
		rs->Reverse();
		rev_mark=0;
	}
}
void abcd :: Reverse()
{
	swap(ls,rs);
	rev_mark^=1;
}
void Zig(abcd *x)
{
	abcd *y=x->fa;
	y->ls=x->rs;
	x->rs->fa=y;
	x->rs=y;
	x->fa=y->fa;
	if(y->fa->ls==y)
		y->fa->ls=x;
	else if(y->fa->rs==y)
		y->fa->rs=x;
	y->fa=x;
	y->Push_Up();
}
void Zag(abcd *x)
{
	abcd *y=x->fa;
	y->rs=x->ls;
	x->ls->fa=y;
	x->ls=y;
	x->fa=y->fa;
	if(y->fa->ls==y)
		y->fa->ls=x;
	else if(y->fa->rs==y)
		y->fa->rs=x;
	y->fa=x;
	y->Push_Up();
}
void Splay(abcd *x)
{
	x->Push_Down();
	while(x->fa->ls==x||x->fa->rs==x)
	{
		abcd *y=x->fa,*z=y->fa;
		if(x==y->ls)
		{
			if(y==z->ls)
				Zig(y);
			Zig(x);
		}
		else
		{
			if(y==z->rs)
				Zag(y);
			Zag(x);
		}
	}
	x->Push_Up();
}
void Access(abcd *x)
{
	abcd *y=null;
	while(x!=null)
	{
		Splay(x);
		x->rs=y;
		x->Push_Up();
		y=x;
		x=x->fa;
	}
}
void Move_To_Root(abcd *x)
{
	Access(x);
	Splay(x);
	x->Reverse();
}
abcd* Find_Root(abcd *x)
{
	while(x->fa!=null)
		x=x->fa;
	return x;
}
void Link(abcd *x,abcd *y)
{
	Move_To_Root(x);
	x->fa=y;
}
void Cut(abcd *x,abcd *y)
{
	Move_To_Root(x);
	Access(y);
	Splay(y);
	x->fa=null;
	y->ls=null;
	y->Push_Up();
}
int n,m;
int main()
{
	
	//freopen("1180.in","r",stdin);
	//freopen("1180.out","w",stdout);
	
	int i,x,y;
	char p[100];
	cin>>n;
	for(i=1;i<=n;i++)
		scanf("%d",&x),tree[i]=new abcd(x);
	cin>>m;
	for(i=1;i<=m;i++)
	{
		scanf("%s%d%d",p,&x,&y);
		if(p[0]=='b')
		{
			if(Find_Root(tree[x])==Find_Root(tree[y]))
				puts("no");
			else
				puts("yes"),Link(tree[x],tree[y]);
		}
		else if(p[0]=='p')
		{
			Splay(tree[x]);
			tree[x]->num=y;
			tree[x]->Push_Up();
		}
		else
		{
			if(Find_Root(tree[x])!=Find_Root(tree[y]))
				puts("impossible");
			else
			{
				Move_To_Root(tree[x]);
				Access(tree[y]);
				Splay(tree[y]);
				printf("%d\n",tree[y]->sum);
			}
		}
	}
	return 0;
}

