#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int maxn=20;
bool can[maxn];
bool temp[maxn];
typedef long long LL;
int n;LL k,rank;
bool judge()
{
	for (int i=1;i<=n;i++){
		if (temp[i]>can[i]) return true;
		if (temp[i]<can[i]) return false;}
	return true;
}
bool search(int now)
{
	if (now==n+1)
	{
		int i;
		for (i=1;i<=n;i++)
			temp[i]=!can[i];
		if (judge()==false) return false;
		for (i=1;i<=n;i++)
			temp[i]=can[n-i+1];
		if (judge()==false) return false;
		for (i=1;i<=n;i++)
			temp[i]=!temp[i];
		if (judge()==false) return false;
		rank++;
	//	for (i=1;i<=n;i++)
	//	printf("%d",can[i]);
	//	printf("\n");
		if (rank==k) 
		{
		for (i=1;i<=n;i++)
	    	printf("%d",can[i]);
	 	printf("\n");
		return true;
		
		}
		return false;
	}
	can[now]=0;
	if (search(now+1))return true;
	can[now]=1;
	if (search(now+1))
	{
		can[now]=0;return true;
	} 
	can[now]=0;
	return false;
	
}
int main()
{
freopen("str.in","r",stdin);
freopen("str.out","w",stdout);
	scanf("%d%lld",&n,&k);
	k++;
	if (n>18) {printf("-1\n");return 0;}
	if (search(1)==false) printf("-1\n");
}
