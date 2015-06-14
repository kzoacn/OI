#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int len[400],lenl[400],lenr[400],n,m,l[400],r[400],num[100001],sum,sz,x,y;
bool a[100001];
int len0[400],lenl0[400],lenr0[400],sum1[400],sum0[400];
int delta[400],op;
bool Spin[400];
int Res,Num;char C,CH[12];
inline int G()
{
    Res=0;C='*'; 
    while(C<'0'||C>'9')C=getchar();
    while(C>='0'&&C<='9'){Res=Res*10+(C-'0');C=getchar();}
    return Res;
}
inline void P(long long x)
{
    Num=0;if(!x){putchar('0');puts("");return;}
    while(x>0)CH[++Num]=x%10,x/=10;
    while(Num)putchar(CH[Num--]+48);
    puts("");
}
void Pushdown(const int &p)
{
    if(delta[p]!=-1)
      {
          for(int i=l[p];i<=r[p];i++) a[i]=delta[p];
          delta[p]=-1;
      }
    else if(Spin[p])
      {
          for(int i=l[p];i<=r[p];i++) a[i]^=1;
          Spin[p]=false;
      }
}
inline void Work(const int &Lb,const int &Rb,const int &sym)
{
    if(sym==0||sym==1) {for(int i=Lb;i<=Rb;i++) a[i]=sym;}
    else if(sym==2) {for(int i=Lb;i<=Rb;i++) a[i]^=1;}
    int cnt=0;
    for(int i=l[num[Lb]];i<=r[num[Lb]];i++) {if(a[i]) break; cnt++;}//??lenl0
    lenl0[num[Lb]]=cnt; cnt=0;
    for(int i=r[num[Lb]];i>=l[num[Lb]];i--) {if(a[i]) break; cnt++;}//??lenr0
    lenr0[num[Lb]]=cnt; cnt=0;
    int Longest=0;
    for(int i=l[num[Lb]];i<=r[num[Lb]];i++)//??len0
      {
          if(a[i]) cnt=0; else cnt++;
          if(cnt>Longest) Longest=cnt;
      }
    len0[num[Lb]]=Longest; cnt=0;
    for(int i=l[num[Lb]];i<=r[num[Lb]];i++) {if(!a[i]) break; cnt++;}//??lenl
    lenl[num[Lb]]=cnt; cnt=0;
    for(int i=r[num[Lb]];i>=l[num[Lb]];i--) {if(!a[i]) break; cnt++;}//??lenr
    lenr[num[Lb]]=cnt; cnt=0; Longest=0;
    for(int i=l[num[Lb]];i<=r[num[Lb]];i++)//??len
      {
          if(!a[i]) cnt=0; else cnt++;
          if(cnt>Longest) Longest=cnt;
      }
    len[num[Lb]]=Longest; cnt=0;
    for(int i=l[num[Lb]];i<=r[num[Lb]];i++) if(a[i]) cnt++;//??sum1 
    sum1[num[Lb]]=cnt; cnt=0;
    for(int i=l[num[Lb]];i<=r[num[Lb]];i++) if(!a[i]) cnt++;//??sum0 
    sum0[num[Lb]]=cnt;
}
void makeblock()
{
    memset(delta,-1,sizeof(delta));
    sz=sqrt((double)n*0.5);
    for(sum=1;sum*sz<n;sum++)
      {
        l[sum]=(sum-1)*sz+1;
        r[sum]=sum*sz;
        for(int i=l[sum];i<=r[sum];i++) num[i]=sum;
        Work(l[sum],r[sum],-1);
      }
    l[sum]=sz*(sum-1)+1; r[sum]=n;
    for(int i=l[sum];i<=r[sum];i++) num[i]=sum;
    Work(l[sum],r[sum],-1);
}
inline void Update(const int &L,const int &R,const bool &sym)
{
    Pushdown(num[L]);
    Pushdown(num[R]);
    if(num[L]==num[R]) Work(L,R,sym);
    else
      {
          Work(L,r[num[L]],sym);
          Work(l[num[R]],R,sym);
          for(int i=num[L]+1;i<num[R];i++)
            {
                if(Spin[i]) Spin[i]=false; delta[i]=sym;
                len[i]=lenl[i]=lenr[i]=sum1[i]=sym ? r[i]-l[i]+1 : 0;
                len0[i]=lenl0[i]=lenr0[i]=sum0[i]=sym ? 0 : r[i]-l[i]+1;
            }
      }
}
inline void Update_Spin(const int &L,const int &R)
{
    Pushdown(num[L]);
    Pushdown(num[R]);
    if(num[L]==num[R]) Work(L,R,2);
    else
      {
          Work(L,r[num[L]],2);
          Work(l[num[R]],R,2);
          for(int i=num[L]+1;i<num[R];i++)
            {
                if(delta[i]==-1) Spin[i]^=1; else delta[i]^=1;
                swap(sum1[i],sum0[i]);
                swap(len[i],len0[i]);
                swap(lenl[i],lenl0[i]);
                swap(lenr[i],lenr0[i]);
            }
      }
}
inline void Query_Sum(const int &L,const int &R)
{
    int ans=0;
    Pushdown(num[L]);
    Pushdown(num[R]);
    if(num[L]==num[R]) {for(int i=L;i<=R;i++) if(a[i]) ans++;}
    else
      {
          for(int i=L;i<=r[num[L]];i++) if(a[i]) ans++;
          for(int i=l[num[R]];i<=R;i++) if(a[i]) ans++;
          for(int i=num[L]+1;i<num[R];i++) ans+=sum1[i];
      }
    P(ans);
}
inline void Query_Len(const int &L,const int &R)
{
    Pushdown(num[L]);
    Pushdown(num[R]);
    int ans=0,cnt=0;
    if(num[L]==num[R])
      {
          for(int i=L;i<=R;i++)
            {
                if(a[i]) cnt++; else cnt=0;
                ans=max(ans,cnt);
            }
          P(ans);
      }
    else
      {
          int kua=0,cntr=0;
        for(int i=r[num[L]];i>=L;i--) {if(!a[i]) break; kua++;}
        for(int i=l[num[R]];i<=R;i++) {if(!a[i]) break; cntr++;}
        for(int i=num[L]+1;i<num[R];i++)
          {
              if(kua) kua+=lenl[i];
            ans=max(ans,kua);
              if(len[i]!=r[i]-l[i]+1) kua=0;
            if(!kua&&lenr[i]) kua=lenr[i];
            ans=max(ans,len[i]);
          }
          for(int i=L;i<=r[num[L]];i++)
            {
                if(a[i]) cnt++; else cnt=0;
                ans=max(ans,cnt);
            } cnt=0;
          for(int i=l[num[R]];i<=R;i++)
            {
                if(a[i]) cnt++; else cnt=0;
                ans=max(ans,cnt);
            }
        P(max(ans,kua+cntr));
      }
}
int main()
{
    n=G();m=G();
    for(int i=1;i<=n;i++) a[i]=G();
    makeblock();
    for(int i=1;i<=m;i++)
      {
          op=G();x=G();y=G();x++;y++;
          if(op==0) Update(x,y,0);
          else if(op==1) Update(x,y,1);
          else if(op==2) Update_Spin(x,y);
          else if(op==3) Query_Sum(x,y);
          else Query_Len(x,y);
      }
    return 0;
}
