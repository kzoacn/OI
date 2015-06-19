#include<set>
#include<map>
#include<ctime>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define inf 2147483647
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,m,tot;
int v[400005],p[400005],a[400005],b[400005];
map<int,int>pid,kid;
char ch[300005][2];
vector<pair<int,int> >q;
struct seg{
	int l,r,mn;
}t[1600005];
void build(int k,int l,int r)
{
	t[k].l=l;t[k].r=r;
	if(l==r){t[k].mn=inf;return;}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	t[k].mn=min(t[k<<1].mn,t[k<<1|1].mn);
}
int query(int k,int x,int y)
{
	int l=t[k].l,r=t[k].r,mid=(l+r)>>1;
	if(x==l&&y==r)return t[k].mn;
	if(y<=mid)return query(k<<1,x,y);
	else if(x>mid)return query(k<<1|1,x,y);
	else return min(query(k<<1,x,mid),query(k<<1|1,mid+1,y));
}
void insert(int k,int x,int val)
{
	int l=t[k].l,r=t[k].r,mid=(l+r)>>1;
	if(l==r){t[k].mn=val;return;}
	if(x<=mid)insert(k<<1,x,val);
	else insert(k<<1|1,x,val);
	t[k].mn=min(t[k<<1].mn,t[k<<1|1].mn);
}
int main()
{
	freopen("bzoj2770.in","r",stdin);
	n=read();m=read();tot=n;
	for(int i=1;i<=n;i++)v[i]=read();
	for(int i=1;i<=n;i++)p[i]=read();
	for(int i=1;i<=n;i++)
		q.push_back(make_pair(v[i],p[i]));
	for(int i=1;i<=m;i++)
	{
		scanf("%s",ch[i]+1);
		a[i]=read();
		if(ch[i][1]!='D')b[i]=read();
		if(ch[i][1]=='I')
		{
			v[++tot]=a[i],p[tot]=b[i];
			q.push_back(make_pair(a[i],b[i]));
		}
	}
	sort(q.begin(),q.end());
	build(1,1,tot);
	for(int i=1;i<=n;i++)
	{
		kid[v[i]]=pid[p[i]]=lower_bound(q.begin(),q.end(),make_pair(v[i],p[i]))-q.begin()+1;
		insert(1,kid[v[i]],p[i]);
	}
	for(int i=1;i<=m;i++)
	{
		if(ch[i][1]=='I')
		{
			kid[a[i]]=pid[b[i]]=lower_bound(q.begin(),q.end(),make_pair(a[i],b[i]))-q.begin()+1;
			insert(1,kid[a[i]],b[i]);
		}
		else if(ch[i][1]=='D')insert(1,kid[a[i]],inf);
		else 
		{
			int t1=kid[a[i]],t2=kid[b[i]]; 
			if(t1>t2)swap(t1,t2);
			int p=query(1,t1,t2);
			printf("%d\n",q[pid[p]-1].first);
		}
	}
	return 0;
}
