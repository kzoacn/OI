#include<bits/stdc++.h>
using namespace std;
typedef long long UL;
const int maxn=5e5+5;
int n,m;
int notp[maxn],p[maxn],minp[maxn];
UL h[maxn],h_l[maxn];
UL get(int l,int r){
    if(l>r)return 0;
    return (h[r]-h[l-1]*h_l[r-l+1]%1000173169+1000173169)%1000173169;  
}
char s[maxn];
int getint(){
    int res=0;char c=getchar();
    while(!isdigit(c))c=getchar();
    while(isdigit(c))res=res*10+c-'0',c=getchar();
    return res;
}
int main(){
    for(int i=2;i<maxn;i++){
        if(!notp[i])minp[i]=i,p[++p[0]]=i;
        for(int j=1;j<=p[0]&&i*p[j]<maxn;j++){
            notp[i*p[j]]=1;minp[i*p[j]]=p[j];
            if(i%p[j]==0)break;
        }
    }
    scanf("%d",&n);int _n=0;
    char c=getchar();while(!isalpha(c))c=getchar();
    while(isalpha(c))s[++_n]=c,c=getchar();h_l[0]=1;
    for(int i=1;i<=n;i++)h_l[i]=h_l[i-1]*31%1000173169;
    for(int i=1;i<=n;i++)h[i]=(h[i-1]*31+s[i])%1000173169;
    for(scanf("%d",&m);m--;){
        int l=getint(),r=getint();
        int len=r-l+1;
        for(int i=len;i>1;){
            int j=minp[i];
            while(len%j==0&&get(l,r-len/j)==get(l+len/j,r))len/=j;
            while(i%j==0)i/=j;
        }printf("%d\n",len);
    }
    return 0;
}
