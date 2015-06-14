#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
char a[maxn];
int getint(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
int n,m;
void putint(int x){
	if(x<10)putchar(x+'0');
	else{putint(x/10);putchar(x%10+'0');}
}
int main(){
	n=getint();m=getint();
	for(int i=1;i<=n;i++)a[i]=-getint();
	while(m--){
		int op=getint();int l=getint()+1,r=getint()+1;
		if(op==0){
			memset(a+l,0,(r-l+1));
		}else if(op==1){
			memset(a+l,-1,(r-l+1));
		}else if(op==2){
			for(int i=l;i<=r;i++)a[i]=-1-a[i];			
		}else if(op==4){
			int ans=0,tmp=0;
			for(int i=l;i<=r;i++){
				if(a[i])tmp++;
				else ans=max(ans,tmp),tmp=0;
			}putint(max(ans,tmp));puts("");
		}else{
			putint(-accumulate(a+l,a+r+1,0)),puts("");
		}//for(int i=1;i<=n;i++)printf("%d%c",-a[i]," \n"[i==n]);
	}	
	return 0;
} 
