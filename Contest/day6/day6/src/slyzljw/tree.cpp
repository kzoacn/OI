#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1001;
const int inf=1e9;
const int maxm=maxn*2;
int val[maxn][2];
int record[maxn][2];
bool can[maxn][2];
int n,q;
int widen=0;
int next[maxm],point[maxn],v[maxm];
int fa[maxn];
int dep[maxn];
void addedge(int x,int y)
{
	widen++;next[widen]=point[x];point[x]=widen;v[widen]=y;
	widen++;next[widen]=point[y];point[y]=widen;v[widen]=x;
}
void search(int now,int f)
{
	fa[now]=f;dep[now]=dep[f]+1;
	for (int k=point[now];k!=0;k=next[k])
	if (v[k]!=f)
	{
		search(v[k],now);
	}
}
int read()
{
	char c=getchar();int bj=1,result=0;
	while (c!='-'&&!(c<='9'&&c>='0')) c=getchar();
	if (c=='-') bj=-1,c=getchar();
	while (c<='9'&&c>='0') result=result*10+c-'0',c=getchar();
	return result*bj;
}
struct save
{ int a[2];
save() {a[0]=a[1]=0;}
};
bool flag;int r=0;
save update(save q,int *num)
{	
	if (num[0]>=0) flag=true;
	if (num[1]>=0) flag=true; 
	save p;
	p.a[0]=max(q.a[0]+num[0],max(q.a[1]+num[1]+num[0],0));
	p.a[1]=max(q.a[1]+num[1],max(q.a[0]+num[1]+num[0],0));
	r=max(r,max(p.a[0],p.a[1]));
	return p;
}
void query(int x,int y)
{
	save ans[2];r=0;
	//int ans[2][2];
	//int ans[0][0]//=max(val[x][0],0),ans[0][1]=max(val[x][1],0),ans[1][0]=max(val[y][0],0),ans[1][1]=max(val[y][1],0);
	//ans[0]=update(save(0,0),val[x]);
	//ans[1]=update(save(0,0),val[y]);
	flag=false;
	while (x!=y)
	{
		if (dep[x]<dep[y]) 
		{
			ans[1]=update(ans[1],val[y]);
			y=fa[y];
		}
		else
		{
			ans[0]=update(ans[0],val[x]);
			x=fa[x];
		}
	}
	int l1=ans[0].a[0],l2=ans[0].a[1],r1=ans[1].a[0],r2=ans[1].a[1];
	r=max(max(l1+r1+val[x][0],l2+r2+val[x][1]),val[x][0]+val[x][1]+max(l1+r2,l2+r1));
	if (val[x][0]>=0||val[x][1]>=0) flag=true;
	if (flag)printf("%d\n",r);
	else printf("Bad Request.\n");
}
char st[10];
int main()
{
	int i,x,y,z;
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n=read();
	for (i=1;i<n;i++) addedge(read(),read());
	for (i=1;i<=n;i++) val[i][0]=val[i][1]=1;
	search(1,0); 
	q=read();
	while (q--)
	{
		scanf("%s",st);
		if (st[0]=='C'&&st[1]=='V')//cval
		{
			x=read();y=read();z=read();
			if (can[x][y]==0)val[x][y]=z;
				else  record[x][y]=z;
		}
		if (st[0]=='C'&&st[1]=='C')
		{
			x=read();y=read();z=read();
			if (z==0) 
			{
				if (can[x][y]==1) 
				{
					can[x][y]=0;
					val[x][y]=record[x][y];
				}
			}
			if(z==1)
			{
				if (can[x][y]==0)
				{
					can[x][y]=1;
					record[x][y]=val[x][y];val[x][y]=-inf;
				}
			}
		}
		if (st[0]=='Q'&&st[1]=='M')
		{
			x=read();y=read();
			query(x,y);
		}
	}
}
