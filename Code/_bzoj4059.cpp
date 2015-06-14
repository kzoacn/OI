#include<iostream>
#include<stdio.h>
#include<string.h>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
#include<set>
#include<map>
#include<time.h>
#define ll long long
#define oo 1<<29
#define MAXN 200005
#define pi acos(-1.0)
#define esp 1e-30
using namespace std;     
struct node
{
       int w,id;
}A[MAXN];
int L[MAXN],R[MAXN];
bool F[MAXN];
bool judge(int s, int e) 
{
       int i,mid;
       if (s==e) return false;
       for (i=0;i<(e-s);i++) 
       {
             if (i%2) mid=s+i/2;
                else  mid=e-1-i/2; 
             if (L[mid]<s && R[mid]>e)
                 return judge(s,mid) || judge(mid+1,e);
       }
       return true;
}
bool cmp(node a,node b)
{
       if (a.w!=b.w) return a.w<b.w;
       else return a.id<b.id;
}
int main()
{    
       int cases,n,i,x; 
       scanf("%d",&cases);  
       while (cases--)
       {   
               scanf("%d",&n);
               for (i=1;i<=n;i++) scanf("%d",&A[i].w),A[i].id=i;
               sort(A+1,A+1+n,cmp),A[n+1].w=A[0].w=-1;
               for (i=1;i<=n;i++)
               { 
                      x=A[i].id;
                      L[x]=0,R[x]=n+1;
                      if (A[i-1].w==A[i].w) L[x]=A[i-1].id;
                      if (A[i+1].w==A[i].w) R[x]=A[i+1].id;
               }
               if (!judge(1,n)) printf("non-boring\n");
                          else  printf("boring\n"); 
       }    
       return 0;
}
