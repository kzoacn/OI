#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MaxN = 300340;
const long long BigNum = 1000000001;
struct Point
{
	double x, y;
	int ind;
	Point(double x, double y, int ind):x(x),y(y),ind(ind){}
	Point() {}
};
int mi, mj;
int n, top;
long long maximum, sum[MaxN], c[MaxN];
Point stack[MaxN];
long long solve()
{
	sum[0] = 0;
	for (int i = 1; i <= n; i++)
		sum[i] = c[i] + sum[i - 1];
	maximum = -700000000000000LL;
	top = 1;
	stack[top] = Point(0.0, 0.0, 1);
	for (int j = 2; j <= n; j++)
	{
		int i = stack[top].ind;
		if (c[j] > 0)
		{
			int left = top;
			int right = 1;
			while (left > right)
			{
				int mid = (left + right) / 2;
				if (c[j] < stack[mid].x)
					right = mid + 1;
				else
					left = mid;
			}
			i = stack[left].ind;
		}
		if (c[j]*(j - i + 1) - sum[j] + sum[i - 1] > maximum)
		{
			maximum = c[j]*(j - i + 1) - sum[j] + sum[i - 1];
			mi = i; mj = j;
		}
		if (sum[j - 1] > stack[top].y)
		{
			while (top > 0 && !(sum[j - 1] - j * stack[top].x < stack[top].y))
				top--;
			top++;
			double x = (sum[j - 1] - stack[top].y - stack[top].ind * stack[top].x) / (j - stack[top].ind);
			double y = sum[j - 1] - j * x;
			int ind = stack[top].ind;
			stack[top++] = Point(x, y, ind);
			stack[top] = Point(0.0, double(sum[j - 1]), j);
		}
	}
	return (sum[n] + maximum - BigNum * n);
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%I64d", &c[i]);
		c[i] += BigNum;
	}
	printf("%I64d\n", solve());
	reverse(c+1,c+1+n);
	printf("%I64d\n", solve());
	return 0;
}
