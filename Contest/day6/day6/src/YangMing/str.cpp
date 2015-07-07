#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

template<class T> inline void RD(T &x)
{
	char c = getchar();	x = 0;	int flg = 0;
	while(c < '0' || c > '9')	flg |= c == '-',c = getchar();
	while(c >= '0' && c <= '9')	x = (x << 1) + (x << 3) + c - '0',c = getchar();
	if(flg)	x = -x;
}

template<class T> inline void RD(T &x,T &y)	{ RD(x);	RD(y); }

inline void setIO(const char *in,const char *out)
{
	if(in)		freopen(in,"r",stdin);
	if(out)		freopen(out,"w",stdout);
}

int N,K;

namespace Solve1
{
	inline void print(int s)
	{
		for(int i = N - 1; ~i ;i --)	putchar('0' + (s >> i & 1));	putchar('\n');
	}
	
	int rev[(1 << 18) + 5];
	inline void main()
	{
		int k = 0,ans = -1;
		rev[0] = 0;	for(int s = 1;s < (1 << N);s ++)	rev[s] = (rev[s >> 1] >> 1) | ((s & 1) << (N - 1));
		for(int s = 1;s < (1 << N) - 1;s ++)
		{
			int t1 = (~s) & ((1 << N) - 1);
			if(t1 < s)	continue ;
			int t2 = rev[s];
			if(t2 < s)	continue ;
			int t3 = (~rev[s]) & ((1 << N) - 1);
			if(t3 < s)	continue ;
			if(++ k == K)	{ ans = s;	break; }
		}
		if(ans == -1)	puts("-1");	else	print(ans);
	}
}

int main()
{
	setIO("str.in","str.out");
	RD(N,K);
	if(N <= 18)	Solve1::main();
	return 0;
}