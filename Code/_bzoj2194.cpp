#include <iostream>
#include <cstdio>
#include <complex>
#include <algorithm>
using namespace std;

const int MaxN = 262144;

const double PI = 3.14159265358979;

inline int getint()
{
   char c;
   while (c = getchar(), '0' > c || c > '9');

   int res = c - '0';
   while (c = getchar(), '0' <= c && c <= '9')
       res = res * 10 + c - '0';
   return res;
}

complex<double> fft_pow[MaxN];

void fft(
       const complex<double> *a,
       const int &n, const int &step,
       complex<double> *out,
       const int type)
{
   if (n == 1)
   {
       out[0] = a[0];
       return;
   }
   
   int m = n >> 1;
   fft(a, m, step << 1, out, type);
   fft(a + step, m, step << 1, out + m, type);
   for (int i = 0; i < m; i++)
   {
       complex<double> even = out[i];
       complex<double> odd = out[i + m];
       if (type == 1)
           odd *= fft_pow[i * step];
       else
           odd /= fft_pow[i * step];
       out[i] = even + odd;
       out[i + m] = even - odd;
   }
}

inline void fft(
       const complex<double> *a, const complex<double> *b,
       int n,
       complex<double> *res)
{
   int tn;
   for (tn = 1; tn < n + n; tn <<= 1);
   n = tn;

   for (int i = 0; i < n; i++)
       fft_pow[i] = exp(complex<double>(0.0, -2 * PI * i / n));

   static complex<double> ta[MaxN];
   static complex<double> tb[MaxN];
   fft(a, n, 1, ta, 1);
   fft(b, n, 1, tb, 1);

   for (int i = 0; i < n; i++)
       ta[i] *= tb[i];

   fft(ta, n, 1, res, -1);

   for (int i = 0; i < n; i++)
       res[i] /= n;
}

int main()
{
	freopen("bzoj2194.in","r",stdin);
   int n;
   static complex<double> a[MaxN];
   static complex<double> b[MaxN];

   cin >> n;
   for (int i = 0; i < n; i++)
       a[i] = getint(), b[i] = getint();

   reverse(a, a + n);

   static complex<double> res[MaxN];
   fft(a, b, n, res);
   reverse(res, res + n);

   for (int i = 0; i < n; i++)
       printf("%d\n", (int)floor(res[i].real() + 0.5));

   return 0;
}
