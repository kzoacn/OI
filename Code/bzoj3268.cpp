#include<stdio.h>
#include<algorithm>
using namespace std;
int getint()
{
	int ret=0;bool ok=false;
	for(;;)
	{
		int c=getchar();
		if(c>='0'&&c<='9')ret=(ret<<3)+ret+ret+c-'0',ok=true;
		else if(ok)return ret;
	}
}
const int maxn=500010;
int n;
int r[maxn],log2[maxn],l[maxn];
typedef pair<int,int> pii;
pii st[maxn][20];
int ask(int L,int R)
{
	if(L<=0)return 0;
	int x=log2[R-L];
	return min(st[L][x],st[R-(1<<x)][x]).second;
}
int pre[maxn][20],arv[maxn][20];
int main()
{
	n=getint();
	for(int i=1;i<=n;i++)r[i]=r[i+n]=getint();
	for(int i=1;i<=n+n;i++)l[i]=max(i-r[i],0);
	for(int i=2;i<=n+n;i++)log2[i]=log2[i-1]+(i==(i&-i));
	for(int i=n+n;i;i--)
	{
		st[i][0]=make_pair(l[i],i);
		for(int j=1;j<=log2[n+n-i+1];j++)st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	}
	for(int i=1;i<=n+n;i++)
	{
		pre[i][0]=i==1?0:ask(l[i],i);
		arv[i][0]=l[i];
		for(int j=1;;j++)
		{
			if(!pre[i][j-1])break;
			pre[i][j]=pre[pre[i][j-1]][j-1];
			arv[i][j]=arv[pre[i][j-1]][j-1];
		}
	}
	long long ans=0;
	for(int i=n;i<=n+n;i++)
	{
		int ret=1;
		int u=i;
		for(int j=19;j>=0;j--)if(arv[u][j])
			if(arv[u][j]>i-n+1)ret+=1<<j,u=pre[u][j];
		ans+=ret;
	}
	printf("%lld\n",ans);
}
