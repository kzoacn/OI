#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
double l[maxn],f[maxn];
char s[maxn];
double sqr(double x){return x*x;}
int main(){
	int n;scanf("%d",&n);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='o'){
			l[i]=l[i-1]+1;
			f[i]=f[i-1]-sqr(l[i-1])+sqr(l[i]);
		}else
		if(s[i]=='x'){
			l[i]=0;
			f[i]=f[i-1];
		}else{
			l[i]=(l[i-1]+1)/2;
			f[i]=f[i-1]+(-sqr(l[i-1])+sqr(l[i]))/2;
		}
	}printf("%.4lf\n",f[n]);
	return 0;
}
