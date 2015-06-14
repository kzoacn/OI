#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
#define MAXT 201000
#define MAXN MAXT
vector<int> query[MAXN];
int query_gets[MAXN];
int cat_gets[MAXN];
int qur_vis[MAXN];
int topq=-1;
struct aaa
{
	int id;
	int fail;
	int qur_id;
	map<int,int> next;
	aaa()
	{
		qur_id=id=fail=-1;
	}
};
int root;
aaa tree[MAXT];
int topt=0;
int name[MAXN],topn=-1;
int str[MAXN];    
int n,m;

void add_str(int * str,int qur)
{
	int ind;
	int now=root;
	map<int,int>::iterator it1;
	while (*str!=-1)
	{
		ind=*(str++);
		it1=tree[now].next.find(ind);
		if (it1==tree[now].next.end())
		{
			tree[now].next.insert(make_pair(ind,++topt));
			tree[topt].id=ind;
			now=topt;
		}else
		{
			now=it1->second;
		}
	}
	if (tree[now].qur_id==-1)
	{
		tree[now].qur_id=++topq;
		query[topq].push_back(qur);
	}else
	{
		query[tree[now].qur_id].push_back(qur);
	}
}
int q[MAXT];
void build_tree()
{
	int ope=0,clo=0,now,temp,x,ind;
	map<int,int>::iterator it1,it2;
	tree[0].fail=0;
	for (it1=tree[0].next.begin();it1!=tree[0].next.end();it1++)
	{
		now=it1->second;
		q[++clo]=now;
		tree[now].fail=0;
	}
	while (ope<clo)
	{
		now=q[++ope];
		for (it1=tree[now].next.begin();it1!=tree[now].next.end();it1++)
		{
			x=it1->second;
			ind=it1->first;
			q[++clo]=x;
			temp=tree[now].fail;
			while (temp!=root)
			{
				it2=tree[temp].next.find(ind);
				if (it2!=tree[temp].next.end())
				{
					tree[x].fail=it2->second;
					break;
				}
				temp=tree[temp].fail;
			}
			it2=tree[root].next.find(ind);
			if (tree[x].fail==-1&&it2!=tree[root].next.end())//Oh, I forgot this part again
			{
				tree[x].fail=it2->second;
			}
			if (tree[x].fail==-1)
			{
				tree[x].fail=0;
			}
		}
	}
}

int count_str(int *str,int cat_id)
{
	int ret=0;
	int now=0;
	int ind,x,temp;
	int i;
	map<int,int>::iterator it1;
	while (*str!=-1)
	{
		ind=*(str++);    
		it1=tree[now].next.find(ind);
		while (now!=root&&it1==tree[now].next.end())
		{
			now=tree[now].fail;
			it1=tree[now].next.find(ind);
		}
		if (it1==tree[now].next.end())
		{
			now=root;
		}else
		{
			now=it1->second;
		}
		temp=now;
		while (temp!=root)
		{
			if (tree[temp].qur_id!=-1)
			{
				x=tree[temp].qur_id;
				for (i=0;i<query[x].size();i++)
				{
					if(qur_vis[query[x][i]]!=cat_id)
					{
						query_gets[query[x][i]]++;
						ret++;
						qur_vis[query[x][i]]=cat_id;
					}
				}
			}
			temp=tree[temp].fail;
		}

	}
	return ret;
}
void init()
{
	topt=0;
	tree[0].id=-1;
	root=0;
	int i,j,x,y;
	scanf("%d%d",&n,&m);
	for (i=0;i<n*2;i++)
	{
		scanf("%d",&x);
		name[++topn]=x;
		for (j=0;j<x;j++)
		{
			scanf("%d",&y);
			name[++topn]=y;
		}
		name[++topn]=-1;
	}
	for (i=0;i<m;i++)
	{
		scanf("%d",&x);
		for (j=0;j<x;j++)
		{
			scanf("%d",&y);
			str[j]=y;
		}
		str[x]=-1;
		add_str(str,i);
	}    
	build_tree();
	memset(qur_vis,-1,sizeof(qur_vis));
}
void work()
{
	int i;
	int now=0;
	for (i=0;i<n*2;i++)
	{
		now++;
		cat_gets[i/2]+=count_str(&name[now],i/2);
		now+=name[now-1];
		now++;
	}
	for (i=0;i<m;i++)
	{
		printf("%d\n",query_gets[i]);
	}
	for (i=0;i<n-1;i++)
	{
		printf("%d ",cat_gets[i]);
	}
	printf("%d\n",cat_gets[n-1]);
}
int main()
{
	init();
	work();
	return 0;
}
