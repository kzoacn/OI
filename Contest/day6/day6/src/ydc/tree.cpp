#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 50010
#define INF 200000000
using namespace std;
inline void max(int &a,int &b,int c,int d)
{
	if(a<c)
		a=c,b=d;
	else if(a==c&&b<d)
		b=d;
}
struct msgnode
{
	int dislen1[2][2],disval1[2][2];
	int dislen2[2][2],disval2[2][2];
	int ldis[2],rdis[2];
	int lval[2],rval[2];
	int minv[2][2];
	int maxlen,maxval;
	int size,sum;
	inline friend msgnode operator + (const msgnode &a,const msgnode &b)
	{
		msgnode c;
		for(int i=0;i<=1;i++)
			c.ldis[i]=c.rdis[i]=c.lval[i]=c.rval[i]=-INF;
		c.maxlen=c.maxval=-INF;
		for(int i=0;i<=1;i++)
			for(int j=0;j<=1;j++)
			{
				c.dislen1[i][j]=-INF;
				c.disval1[i][j]=-INF;
				c.dislen2[i][j]=-INF;
				c.disval2[i][j]=-INF;
				c.minv[i][j]=INF;
				for(int k=0;k<=1;k++)
				{
					max(c.disval1[i][j],c.dislen1[i][j],a.disval1[i][k]+b.disval1[k][j],a.dislen1[i][k]+b.dislen1[k][j]);
					max(c.disval2[i][j],c.dislen2[i][j],b.disval2[k][j]+a.disval2[i][k],b.dislen2[k][j]+a.dislen2[i][k]);
					max(c.lval[i],c.ldis[i],a.disval1[i][k]+b.lval[k],a.dislen1[i][k]+b.ldis[k]);
					max(c.rval[j],c.rdis[j],b.disval2[k][j]+a.rval[k],b.dislen2[k][j]+a.rdis[k]);
					c.minv[i][j]=min(c.minv[i][j],min(a.minv[i][k],b.minv[k][j]));
				}
				max(c.lval[i],c.ldis[i],a.lval[i],a.ldis[i]);
				max(c.rval[j],c.rdis[j],b.rval[j],b.rdis[j]);
			}
		max(c.maxval,c.maxlen,a.maxval,a.maxlen);
		max(c.maxval,c.maxlen,b.maxval,b.maxlen);
		for(int k=0;k<=1;k++)
			max(c.maxval,c.maxlen,a.rval[k]+b.lval[k],a.rdis[k]+b.ldis[k]);
		c.size=a.size+b.size;
		c.sum=a.sum+b.sum;
		return c;
	}
};
struct Link_Cut_Tree
{
	int son[maxn][2],father[maxn],value[maxn][2];
	bool flag[maxn],color[maxn][2],set[maxn];
	msgnode msg[maxn];
	msgnode get(int p)
	{
		msgnode ans;
		ans.size=2,ans.sum=value[p][0]+value[p][1];
		ans.maxlen=-INF,ans.maxval=-INF;
		for(int i=0;i<=1;i++)
			ans.ldis[i]=ans.rdis[i]=ans.lval[i]=ans.rval[i]=-INF;
		for(int i=0;i<=1;i++)
			for(int j=0;j<=1;j++)
			{
				ans.minv[i][j]=min(value[p][i],value[p][j]);
				if(color[p][i]&&color[p][j])
				{
					ans.dislen1[i][j]=ans.dislen2[i][j]=(i==j?1:2);
					ans.disval1[i][j]=ans.disval2[i][j]=(i==j?value[p][i]:value[p][i]+value[p][j]);
					max(ans.maxval,ans.maxlen,ans.disval1[i][j],ans.dislen1[i][j]);
					max(ans.lval[i],ans.ldis[i],ans.disval1[i][j],ans.dislen1[i][j]);
					max(ans.rval[j],ans.rdis[j],ans.disval2[i][j],ans.dislen2[i][j]);
				}
				else
				{
					ans.dislen1[i][j]=-INF;
					ans.dislen2[i][j]=-INF;
					ans.disval1[i][j]=-INF;
					ans.disval2[i][j]=-INF;
				}
			}
		return ans;
	}
	bool Root(int p)
	{
		return p!=son[father[p]][0]&&p!=son[father[p]][1];
	}
	void Build(int n)
	{
		for(int i=1;i<=n;i++)
		{
			value[i][0]=1;
			value[i][1]=1;
			color[i][0]=true;
			color[i][1]=true;
			msg[i]=get(i);
		}
	}
	void update_set(int p,bool col)
	{
		msgnode ans;
		flag[p]=true,set[p]=col;
		color[p][0]=color[p][1]=col;
		if(col==true)
		{
			if((msg[p].size/2)&1)
			{
				ans.dislen1[0][1]=ans.dislen1[1][0]=msg[p].size;
				ans.dislen2[0][1]=ans.dislen2[1][0]=msg[p].size;
				ans.disval1[0][1]=ans.disval1[1][0]=msg[p].sum;
				ans.disval2[0][1]=ans.disval2[1][0]=msg[p].sum;
				ans.dislen1[0][0]=ans.dislen1[1][1]=msg[p].size-1;
				ans.dislen2[0][0]=ans.dislen2[1][1]=msg[p].size-1;
				ans.disval1[0][0]=ans.disval2[0][0]=msg[p].sum-msg[p].minv[0][0];
				ans.disval1[1][1]=ans.disval2[1][1]=msg[p].sum-msg[p].minv[1][1];
			}
			else
			{
				ans.dislen1[0][0]=ans.dislen1[1][1]=msg[p].size;
				ans.dislen2[0][0]=ans.dislen2[1][1]=msg[p].size;
				ans.disval1[0][0]=ans.disval1[1][1]=msg[p].sum;
				ans.disval2[0][0]=ans.disval2[1][1]=msg[p].sum;
				ans.dislen1[0][1]=ans.dislen1[1][0]=msg[p].size-1;
				ans.dislen2[0][1]=ans.dislen2[1][0]=msg[p].size-1;
				ans.disval1[0][1]=ans.disval2[0][1]=msg[p].sum-msg[p].minv[0][1];
				ans.disval1[1][0]=ans.disval2[1][0]=msg[p].sum-msg[p].minv[1][0];
			}
			ans.maxlen=msg[p].size;
			ans.maxval=msg[p].sum;
			for(int i=0;i<=1;i++)
			{
				ans.ldis[i]=msg[p].size;
				ans.rdis[i]=msg[p].size;
				ans.lval[i]=msg[p].sum;
				ans.rval[i]=msg[p].sum;
			}
		}
		else
		{
			for(int i=0;i<=1;i++)
				for(int j=0;j<=1;j++)
				{
					ans.dislen1[i][j]=-INF;
					ans.dislen2[i][j]=-INF;
					ans.disval1[i][j]=-INF;
					ans.disval2[i][j]=-INF;
				}
			ans.maxlen=-INF;
			ans.maxval=-INF;
			for(int i=0;i<=1;i++)
			{
				ans.ldis[i]=-INF;
				ans.rdis[i]=-INF;
				ans.lval[i]=-INF;
				ans.rval[i]=-INF;
			}
		}
		ans.size=msg[p].size,ans.sum=msg[p].sum;
		for(int i=0;i<=1;i++)
			for(int j=0;j<=1;j++)
				ans.minv[i][j]=msg[p].minv[i][j];
		msg[p]=ans;
	}
	void update(int p)
	{
		msg[p]=get(p);
		if(son[p][0])
			msg[p]=msg[son[p][0]]+msg[p];
		if(son[p][1])
			msg[p]=msg[p]+msg[son[p][1]];
	}
	void push_down(int p)
	{
		if(flag[p])
		{
			if(son[p][0])
				update_set(son[p][0],set[p]);
			if(son[p][1])
				update_set(son[p][1],set[p]);
			flag[p]=false,set[p]=0;
		}
	}
	void Rotate(int p,int x)
	{
		int mark=p==son[x][1],y=son[p][mark^1],z=father[x];
		if(y!=0)
			father[y]=x;
		if(x==son[z][0])
			son[z][0]=p;
		if(x==son[z][1])
			son[z][1]=p;
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
	void Access(int p)
	{
		for(int v=0;p;v=p,p=father[p])
			Splay(p),son[p][1]=v,update(p);
	}
	void Set(int x,int y,int z)
	{
		Access(x);
		for(int p=y,v=0;p;v=p,p=father[p])
		{
			Splay(p);
			if(father[p]==0)
			{
				color[p][0]=color[p][1]=z;
				if(son[p][1])
					update_set(son[p][1],z);
				if(v)
					update_set(v,z);
			}
			son[p][1]=v,update(p);
		}
	}
	void Cval(int a,int b,int c)
	{
		Splay(a);
		value[a][b]=c;
		update(a);
	}
	void Ccolor(int a,int b,int c)
	{
		Splay(a);
		color[a][b]=c;
		update(a);
	}
	msgnode Query(int x,int y)
	{
		Access(x);
		for(int p=y,v=0;p;v=p,p=father[p])
		{
			Splay(p);
			if(father[p]==0)
			{
				msgnode ans=get(p);
				if(son[p][1])
				{
					msgnode temp=msg[son[p][1]];
					for(int i=0;i<=1;i++)
						for(int j=0;j<=1;j++)
						{
							swap(temp.dislen1[i][j],temp.dislen2[i][j]);
							swap(temp.disval1[i][j],temp.disval2[i][j]);
						}
					swap(temp.ldis[0],temp.rdis[0]);
					swap(temp.ldis[1],temp.rdis[1]);
					swap(temp.lval[0],temp.rval[0]);
					swap(temp.lval[1],temp.rval[1]);
					ans=temp+ans;
				}
				if(v)
					ans=ans+msg[v];
				return ans;
			}
			son[p][1]=v,update(p);
		}
	}
}tree;
int n;
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
int nEdge,to[maxn*2],next[maxn*2],start[maxn];
void make(int a,int b)
{
	nEdge++,to[nEdge]=b,next[nEdge]=start[a],start[a]=nEdge;
}
void BFS(int p)
{
	static int queue[maxn];
	static bool use[maxn];
	int front=0,rear=1;
	queue[rear]=p,use[p]=true;
	while(front<rear)
	{
		int p=queue[++front];
		for(int i=start[p],q;i;i=next[i])
			if(use[q=to[i]]==false)
			{
				use[q]=true;
				queue[++rear]=q;
				tree.father[q]=p;
				if(tree.son[p][1]==0)
					tree.son[p][1]=q;
			}
	}
	for(int i=1;i<=n;i++)
		if(tree.son[i][1]==0)
			tree.Splay(i);
}
void read()
{
	Read(n);
	tree.Build(n);
	for(int i=2,a,b;i<=n;i++)
	{
		Read(a),Read(b);
		make(a,b),make(b,a);
	}
	BFS(1);
}
void Query()
{
	char task[10];
	int m;
	Read(m);
	for(int i=1,a,b,c;i<=m;i++)
	{
		scanf("%s",task);
		if(strcmp(task,"CVal")==0)
		{
			Read(a),Read(b),Read(c);
			tree.Cval(a,b,c);
		}
		if(strcmp(task,"CColor")==0)
		{
			Read(a),Read(b),Read(c);
			tree.Ccolor(a,b,c^1);
		}
		if(strcmp(task,"Cover")==0)
		{
			Read(a),Read(b),Read(c);
			tree.Set(a,b,c^1);
		}
		if(task[0]=='Q')
		{
			Read(a),Read(b);
			msgnode ans=tree.Query(a,b);
			if(task[1]=='M')
			{
				if(ans.maxval<0)
					printf("Bad Request.\n");
				else
					printf("%d\n",ans.maxval);
			}
			else
				printf("%d\n",max(ans.maxlen,0));
		}
	}
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	read();
	Query();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
