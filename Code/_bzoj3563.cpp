#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
typedef unsigned long long uLL;
const int maxn=100011,maxm=500011,maxbit=64;
int n,m,q,k,widen=1;
int next[maxm*2],point[maxn],v[maxm*2],deep[maxn];
uLL w[maxm],value[maxn],a[maxm];
bool tree[maxm];
inline void addedge(int x,int y)
{
	widen++;next[widen]=point[x];point[x]=widen;v[widen]=y;
	widen++;next[widen]=point[y];point[y]=widen;v[widen]=x;
}
inline uLL getrand()
{
	return 1ull*rand()*rand()*rand();
}
inline void dfs1(int now,int fa)
{
	deep[now]=deep[fa]+1;
	for (int k=point[now];k!=0;k=next[k])
	if (deep[v[k]]==0)
	{
		tree[k>>1]=true;
		dfs1(v[k],now);
	}
	else if (v[k]!=fa&&deep[v[k]]<deep[now])
	{
		w[k>>1]=getrand();
		while(w[k>>1]==0) w[k>>1]=getrand();
		value[now]^=w[k>>1];
		value[v[k]]^=w[k>>1];
	}
}
inline void dfs2(int now,int fa)
{
	for (int k=point[now];k!=0;k=next[k])
	if (v[k]!=fa&&tree[k>>1])
	{
		dfs2(v[k],now);
		w[k>>1]=value[v[k]];
		value[now]^=value[v[k]];
	}
}
inline bool judge()
{
	int i,j,now;
	for (now=1,i=maxbit;now<=k&&i>=1;i--)
	{
		for (j=now;j<=k;j++)
		if ((a[j]>>(i-1))&1) break;
		if (j>k) continue;
		swap(a[now],a[j]);
		for(j=now+1;j<=k;j++)
			if ((a[j]>>(i-1))&1) a[j]^=a[now];
		now++;
	}
	if (now<=k) return true;
	return false;
}
inline int read()
{
	char c=getchar();int bj=1,result=0;
	while(c!='-'&&!(c<='9'&&c>='0')) c=getchar();
	if(c=='-') bj=-1,c=getchar();
	while(c<='9'&&c>='0') result=result*10+c-'0',c=getchar();
	return result*bj; 
}
int main()
{
	srand(2333);
	n=read();m=read();
	for (int i=1;i<=m;i++) 	addedge(read(),read());
	dfs1(1,0);dfs2(1,0);
	q=read();int lastans=0;
	while(q--)
	{
		k=read();//k=read()^lastans;bzoj3563
		for (int i=1;i<=k;i++) a[i]=w[read()^lastans];
		if(judge())printf("Disconnected\n");
		else {lastans++;printf("Connected\n");}
		lastans=0;
	}
}
