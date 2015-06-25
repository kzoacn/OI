#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e6+5;
int next[maxn],slen,tlen;
char s[maxn],t[maxn];
int kmp(){
	int ans=0;
	for(int i=2,j=next[1]=0;i<=tlen;++i){
		while(j&&t[i]!=t[j+1])j=next[j];
		next[i]=j+=t[i]==t[j+1];
	}for(int i=1,j=0;i<=slen;i++){
		while(j&&s[i]!=t[j+1])j=next[j];
		j+=s[i]==t[j+1];
		if(j==tlen)j=next[j],ans++;
	}return ans;
}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%s%s",t+1,s+1);
		slen=strlen(s+1);
		tlen=strlen(t+1);
		printf("%d\n",kmp());
	}	
	return 0;
}
