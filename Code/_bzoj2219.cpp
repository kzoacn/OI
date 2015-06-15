#include<iostream>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cstdio>
#include<cmath>
#define hashmod 10007
#define CNT 300000
using namespace std;
int qp(int a,int b){int ans=1;do{if(b&1)ans*=a;a*=a;}while(b>>=1);return ans;}
int qp(int a,int b,int mo){int ans=1;do{if(b&1)ans=1ll*ans*a%mo;a=1ll*a*a%mo;}while(b>>=1);return ans;}
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int divs[500];int dtot=0;
int proot(int p){
    dtot=0;
    int q=p-1;
    for (int i=2;i*i<=q;i++)
        if(q%i==0){
            divs[dtot++]=i;
            if(q!=i*i)divs[dtot++]=q/i;
        }
    for (int i=2;i<p;i++){
        int ok=1;
        for (int j=0;j<dtot;j++)if(qp(i,divs[j],p)==1){
            ok=0;break;
        }
        if(ok)return i;
    }
}
struct H{
    int head[hashmod];
    int S[CNT],V[CNT],next[CNT];
    int tot;
    void cl(){
        tot=0;
        memset(head,-1,sizeof(head));
    }
    int push(int s,int v){
        for (int i=head[s%hashmod];~i;i=next[i])if(S[i]==s)return V[i];
        S[tot]=s;V[tot]=v;next[tot]=head[s%hashmod];head[s%hashmod]=tot++;
        return v;
    }
}has;
              
int solve(int a,int b,int p,int al){
    int pa=qp(p,al);b%=pa;
    if(b==0){
        return qp(p,al-((al-1)/a+1));
    }else{
        int bet=0;
        while(b%p==0)b/=p,bet++;
        if(bet%a)return 0;
int tt=bet/a;
        al-=bet;
        int phi=pa-pa/p;
        int g=proot(p);
        has.cl();
        int m=int(sqrt(pa))+1;
        int gm=qp(g,m,pa);
        int cur=1;
        for (int i=1;i<=m;i++){
            cur=1ll*cur*gm%pa;
            has.push(cur,i);
        }
        cur=b;
        int ind=2000000000;
        for (int j=1;j<=m;j++){
            cur=1ll*cur*g%pa;
            int tmp;if(tmp=has.push(cur,0))ind=min(ind,tmp*m-j);
        }
        int d=gcd(a,phi);
        if(ind%d)return 0;
        return d*qp(p,(a-1)*tt);
    }
}
              
          
          
int main()
{
	freopen("bzoj2219.in","r",stdin);
    int tes;
    scanf("%d",&tes);
    while(tes--){
        int a,b,k;
        scanf("%d%d%d",&a,&b,&k);k=2*k+1;
        int ans=1;
        for (int i=2;i*i<=k && ans;i++)if(k%i==0){
            int al=0;
            while(k%i==0)al++,k/=i;
            ans*=solve(a,b,i,al);
        }
        if(ans && k!=1)ans*=solve(a,b,k,1);
        printf("%d\n",ans);
    }
    return 0;
}
