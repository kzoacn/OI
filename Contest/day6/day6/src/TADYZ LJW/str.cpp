#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<set>
#include<stack>
#include<cstdlib>
#include<string>
#include<bitset>
#include<map>
#define INF 1000000000
#define N 100005
#define fi first
#define se second
#define debug(x) cout<<#x<<"="<<x<<endl
#define MP(x,y) make_pair(x,y)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
int ans[55];
int main()
{
	int i,j,n,l,s,now,h,t,s2,st,m,t1,t2,flag=0,f1;
	LL k;
	freopen("str.in","r",stdin);
	freopen("str.out","w",stdout);
	cin>>n>>k;
	if(n%2==0)
	{
		f1=0;
		s=1<<n/2;
		m=n/2;
		l=m;
		if(k<=s-1)
			h=0;
		else
		{
			k-=s-1;
			h=-1;
			now=s-2;
			for(i=1;i<s&&now;i++,now-=2)
				if(k<=now)
				{
					h=i;
					break;
				}
				else
					k-=now;
		}
		if(h==-1)
		{
			printf("-1\n");
			return 0;
		}
	}
	else
	{
		f1=1;
		s=1<<n/2;
		s2=1<<(n+1)/2;
		m=(n+1)/2;
		l=m-1;
		if(k<=s-1)
			h=0;
		else
		{
			k-=s-1;
			h=-1;
			now=s-1;
			for(i=1;i<s2&&now;i++,now--)
				if(k<=now)
				{
					h=i;
					break;
				}
				else
					k-=now;
		}
		if(h==-1)
		{
			printf("-1\n");
			return 0;
		}
	}
	if(now-k>=k)
	{
		//debug(123);
		if(h==0)
			st=1;
		else st=0;
		//debug(s);
		for(i=st;i<s;i++)
		{
			flag=1;
			//debug(i);
			if(i&1)
			{
				t1=0;
				t2=0;
				for(j=0;j<l;j++)
				{
					t1=h>>(l-j-1);
					if(i&(1<<j))
						t2=(t2<<1);
					else t2=t2<<1|1;
					//(t1);
					//debug(t2);
					if(t1>t2)
					{
						flag=0;
						break;
					}
					else if(t1<t2)
					{
						//flag=1;
						break;
					}
				}
				if(t1==t2&&(h&1)&&f1)
					flag=0;
			}
			else
			{
				t1=0;
				t2=0;
				for(j=0;j<l;j++)
				{
					t1=h>>(l-j-1);
					if(i&(1<<j))
						t2=(t2<<1)|1;
					else t2=t2<<1;
					//debug(t1);
					//debug(t2);
					if(t1>t2)
					{
						flag=0;
						break;
					}
					else if(t1<t2)
					{
						//flag=1;
						break;
					}
				}
			}
			k-=flag;
			if(!k)
			{
				t=i;
				break;
			}
		}
	}
	else
	{
		k=now-k+1;
		st=s-1;
		for(i=st;i>=0;i--)
		{
			flag=1;	
			if(i&1)
			{
				t1=0;
				t2=0;
				for(j=0;j<l;j++)
				{
					t1=h>>(l-j-1);
					if(i&(1<<j))
						t2=(t2<<1);
					else t2=t2<<1|1;
					if(t1>t2)
					{
						flag=0;
						break;
					}
					else if(t1<t2)
					{
						//flag=1;
						break;
					}
				}
				if(t1==t2&&(h&1)&&f1)
					flag=0;
			}
			else
			{
				t1=0;
				t2=0;
				for(j=0;j<l;j++)
				{
					t1=h>>(l-j-1);
					if(i&(1<<j))
						t2=(t2<<1)|1;
					else t2=t2<<1;
					if(t1>t2)
					{
						flag=0;
						break;
					}
					else if(t1<t2)
					{
						//flag=1;
						break;
					}
				}
			}
			k-=flag;
			if(!k)
			{
				t=i;
				break;
			}
		}
	}
	for(i=0;i<l;i++)
		if((1<<i)&t)
			ans[i]=1;
		else ans[i]=0;
	for(i=l;i<n;i++)
		if((1<<i-l)&h)
			ans[i]=1;
		else ans[i]=0;
	reverse(ans,ans+n);
	for(i=0;i<n;i++)
		printf("%d",ans[i]);
	cout<<endl;
	return 0;
}
// davidlee1999WTK 2015/
// srO myk Orz
//ios::sync_with_stdio(false);

