#include<cstdio>
#include<vector>

std::vector<int> g[222222];
int xx[222222];
int yy[222222];
int v[222222];

void dfs(int x,int y)
{
	if(v[x])return;
	int i;
	v[x]=y;
	for(i=0;i<g[x].size();i++)dfs(g[x][i],3-y);
}

int main()
{
	int x,y;
	int i,n;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		if(xx[x])
		{
			g[i].push_back(xx[x]);
			g[xx[x]].push_back(i);
			xx[x]=0;
		}
		else xx[x]=i;
		if(yy[y])
		{
			g[i].push_back(yy[y]);
			g[yy[y]].push_back(i);
			yy[y]=0;
		}
		else yy[y]=i;
	}
	for(i=1;i<=n;i++)
	{
		dfs(i,1);
		putchar(v[i]>1?'b':'r');
	}
}
