#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 1001001
#define MOD 1000000007
using namespace std;
int n,k;
long long fac[M],inv[M],ans;
void Linear_Shaker()
{
    int i;
    fac[0]=1;
    for(i=1;i<=n;i++)
        fac[i]=fac[i-1]*i%MOD;
    inv[1]=1;
    for(i=2;i<=n;i++)
        inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
    inv[0]=1;
    for(i=1;i<=n;i++)
        (inv[i]*=inv[i-1])%=MOD;
}
long long C(long long n,long long m)
{
    return fac[n] * inv[m] % MOD * inv[n-m] % MOD;
}
int main()
{
    int i;
    cin>>n>>k;
    Linear_Shaker();
    long long temp=2;
    for(i=n;i>=k;i--)
    {
        if(i!=n) (temp*=temp)%=MOD;
        ans+= (i-k&1?MOD-1:1) * C(n,i) % MOD * C(i,k) % MOD * temp % MOD;
        ans%=MOD;
    }
    cout<<ans<<endl;
    return 0;
}
