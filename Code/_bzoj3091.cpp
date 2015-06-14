#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 50010
using namespace std;
typedef long long LL;
LL gcd(LL a,LL b)
{
	return a%b?gcd(b,a%b):b;
}
LL sigma1(LL n)
{
	return n*(n+1)/2;
}
LL sigma2(LL n)
{
	return n*(n+1)*(n+2)/6;
}
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
struct tagnode
{
	bool rev;
	LL delta;
};
struct msgnode
{
	LL sumpre,sumsuf,size,ans,sum;
	msgnode() {}
	msgnode(int val)
	{
		size=1;
		sumpre=sumsuf=sum=ans=val;
	}
	friend msgnode operator + (const msgnode &a,const msgnode &b)
	{
		msgnode c;
		c.size=a.size+b.size;
		c.sum=a.sum+b.sum;
		c.ans=a.ans+b.ans+a.sumsuf*b.size+b.sumpre*a.size;
		c.sumpre=a.sumpre+b.sumpre+a.sum*b.size;
		c.sumsuf=a.sumsuf+b.sumsuf+a.size*b.sum;
		return c;
	}
};
struct LCT
{
	int son[maxn][2],father[maxn],val[maxn];
	msgnode msg[maxn];
	tagnode tag[maxn];
	bool Root(int p)
	{
		return p!=son[father[p]][0]&&p!=son[father[p]][1];
	}
	void update(int p)
	{
		msg[p]=msgnode(val[p]);
		if(son[p][0])
			msg[p]=msg[son[p][0]]+msg[p];
		if(son[p][1])
			msg[p]=msg[p]+msg[son[p][1]];
	}
	void Access(int p)
	{
		for(int v=0;p;v=p,p=father[p])
			Splay(p),son[p][1]=v,update(p);
	}
	void push_down(int p)
	{
		if(tag[p].rev)
		{
			if(son[p][0])
				update_rev(son[p][0]);
			if(son[p][1])
				update_rev(son[p][1]);
			tag[p].rev=false;
		}
		if(tag[p].delta)
		{
			if(son[p][0])
				update_add(son[p][0],tag[p].delta);
			if(son[p][1])
				update_add(son[p][1],tag[p].delta);
			tag[p].delta=0;
		}
	}
	void Rotate(int p,int x)
	{
		int mark=p==son[x][1],y=son[p][mark^1],z=father[x];
		if(y!=0)
			father[y]=x;
		if(x==son[z][1])
			son[z][1]=p;
		if(x==son[z][0])
			son[z][0]=p;
		son[p][mark^1]=x,father[p]=z,son[x][mark]=y,father[x]=p,update(x);
	}
	void Splay(int p)
	{
		static int ancestor[maxn],top;
		ancestor[++top]=p;
		for(int i=p;!Root(i);i=father[i])
			ancestor[++top]=father[i];
		for(;top;top--)
			push_down(ancestor[top]);
		while(!Root(p))
		{
			int x=father[p],y=father[x];
			if(Root(x))
				Rotate(p,x);
			else if((p==son[x][0])^(x==son[y][0]))
				Rotate(p,x),Rotate(p,y);
			else
				Rotate(x,y),Rotate(p,x);
		}
		update(p);
	}
	int FindRoot(int p)
	{
		Access(p);
		Splay(p);
		for(;son[p][0];p=son[p][0])
			push_down(p);
		Splay(p);
		return p;
	}
	void BeRoot(int a)
	{
		Access(a);
		Splay(a);
		update_rev(a);
	}
	void update_rev(int p)
	{
		tag[p].rev^=1;
		swap(msg[p].sumpre,msg[p].sumsuf);
		swap(son[p][0],son[p][1]);
	}
	void update_add(int p,LL &delta)
	{
		val[p]+=delta;
		tag[p].delta+=delta;
		msg[p].sum=msg[p].sum+delta*msg[p].size;
		msg[p].sumpre=msg[p].sumpre+sigma1(msg[p].size)*delta;
		msg[p].sumsuf=msg[p].sumsuf+sigma1(msg[p].size)*delta;
		msg[p].ans=msg[p].ans+sigma2(msg[p].size)*delta;
	}
	void Link(int a,int b)
	{
		if(FindRoot(a)==FindRoot(b))
			return ;
		BeRoot(a),BeRoot(b);
		father[a]=b;
	}
	void cut(int a,int b)
	{
		BeRoot(a);
		Access(b);
		Splay(b);
		if(son[b][0]!=a||son[a][0]||son[a][1])
			return ;
		son[b][0]=0,father[a]=0,update(b);
	}
	void increase(int a,int b,LL c)
	{
		if(FindRoot(a)!=FindRoot(b))
			return ;
		Access(a);
		for(int p=b,v=0;p;v=p,p=father[p])
		{
			Splay(p);
			if(father[p]==0)
			{
				val[p]+=c;
				if(son[p][1])
					update_add(son[p][1],c);
				if(v)
					update_add(v,c);
			}
			son[p][1]=v,update(p);
		}
	}
	void Query(int a,int b)
	{
		if(FindRoot(a)!=FindRoot(b))
		{
			printf("-1\n");
			return ;
		}
		Access(a);
		for(int p=b,v=0;p;v=p,p=father[p])
		{
			Splay(p);
			if(father[p]==0)
			{
				msgnode ans=msgnode(val[p]);
				if(son[p][1])
				{
					msgnode temp=msg[son[p][1]];
					swap(temp.sumpre,temp.sumsuf);
					ans=temp+ans;
				}
				if(v)
					ans=ans+msg[v];
				LL x=ans.ans,y=sigma1(ans.size),k=gcd(x,y);
				x/=k,y/=k;
				printf("%lld/%lld\n",x,y);
			}
			son[p][1]=v,update(p);
		}
	}
}tree;
void read()
{
	int n,m;
	Read(n),Read(m);
	for(int i=1;i<=n;i++)
	{		
		Read(tree.val[i]);
		tree.update(i);
	}
	for(int i=2,a,b;i<=n;i++)
	{
		Read(a),Read(b);
		tree.Link(a,b);
	}
	for(int i=1,type,a,b,c;i<=m;i++)
	{
		Read(type);
		if(type==1)
		{
			Read(a),Read(b);
			tree.cut(a,b);
		}
		if(type==2)
		{
			Read(a),Read(b);
			tree.Link(a,b);
		}
		if(type==3)
		{
			Read(a),Read(b),Read(c);
			tree.increase(a,b,c);
		}
		if(type==4)
		{
			Read(a),Read(b);
			tree.Query(a,b);
		}
	}
}
int main()
{
	
//	freopen("bzoj3091.in","r",stdin);
	read();
	return 0;
}
/*
	ORZ vfleaking
*/
