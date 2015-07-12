#include<bits/stdc++.h>
#include<ext/rope>
using namespace std;
using namespace __gnu_cxx;
const int maxn=3e6+5;
int m,ty;
char s[maxn];
int la;
void decode(char *s,int len){
	for(int i=0;i<len;i++)s[i]=(s[i]-'a'+1+la)%26+'a';
}
crope R,tmp1,tmp2,tmp;
void I(int k,char *s,int len){
	tmp=crope(s,s+len);
	R.insert(k,tmp);
}
int Q(int l,int r,char *s,int len){
	
}
int main(){
	scanf("%d%d",&m,&ty);
	while(m--){
		char op[2];scanf("%s",op);
		if(*op=='I'){
			int k;scanf("%d%s",&k,s);
			int len=strlen(s);
			if(ty)k^=la,decode(s,len);
			I(k,s,len);
		}else{
			int l,r;scanf("%d%d%s",&l,&r,s);
			int len=strlen(s);
			if(ty)l^=la,r^=la,decode(s,len);
			if(l>r)swap(l,r);
			printf("%d\n",Q(l,r,s,len));
		}
	}
	return 0;
}
