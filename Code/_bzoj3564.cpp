#include<cstdio>

#include<iostream>

#include<cstring>

#include<algorithm>

#include<cmath>

using namespace std;

#define sqr(x) ((x)*(x))

#define fi first

#define se second

#define maxn 100100

typedef pair<double,double> ii;

ii a[maxn],cir;

double r;

double dis(ii x,ii y) {

return sqrt(sqr(x.fi-y.fi)+sqr(x.se-y.se));

}

ii getcir(ii x,ii y,ii z){

double a=sqr(x.fi)-sqr(y.fi)+sqr(x.se)-sqr(y.se),

  b=sqr(x.fi)-sqr(z.fi)+sqr(x.se)-sqr(z.se),

  c=2*(x.se-z.se)*(x.fi-y.fi)-2*(x.se-y.se)*(x.fi-z.fi);

return ii((a*(x.se-z.se)-b*(x.se-y.se))/c,

(a*(x.fi-z.fi)-b*(x.fi-y.fi))/(-c));

}

#define exp 1e-10

int cmp(double x) {

if (x<-exp) return -1;

if (x>exp) return 1;

return 0;

}

int n;

const double pi=acos(-1);

int main(){


scanf("%d",&n);

for (int i=1;i<=n;i++) scanf("%lf%lf",&a[i].fi,&a[i].se);

double tmp;

scanf("%lf",&tmp);

tmp*=-pi/180;

for (int i=1;i<=n;i++) a[i]=ii(a[i].fi*cos(tmp)-a[i].se*sin(tmp),

a[i].fi*sin(tmp)+a[i].se*cos(tmp));

scanf("%lf",&tmp);

for (int i=1;i<=n;i++) a[i].fi/=tmp;

random_shuffle(a+1,a+1+n);

cir=a[1],r=0;

for (int i=1;i<=n;i++) {

if (cmp(dis(cir,a[i])-r)<=0) continue;

cir=a[i],r=0;

for (int j=1;j<i;j++) {

if (cmp(dis(cir,a[j])-r)<=0) continue;

cir.fi=(a[i].fi+a[j].fi)/2,cir.se=(a[i].se+a[j].se)/2;

r=dis(cir,a[j]);

for (int k=1;k<j;k++) {

if (cmp(dis(cir,a[k])-r)<=0) continue;

cir=getcir(a[i],a[j],a[k]);

r=dis(cir,a[i]);

}

}

}

printf("%.3lf\n",r);

return 0;

}
