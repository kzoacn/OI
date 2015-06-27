#include<bits/stdc++.h>
using namespace std;
const int maxn=27;
int n;
char s[101][101];
int l[101];
int w[maxn][maxn];
int tmp[maxn];
int cmp(int x,int y){
	return w[0][x]<w[0][y];
}
int find(char x){
	for(int i=1;i<=26;i++)if(tmp[i]-1+'a'==x)return i;
}
bool com(char a,char b){
	return find(a)<find(b);
}
bool com(string a,string b){
	for(int i=0;i<min(a.length(),b.length());i++)
		if(com(a[i],b[i]))return 1;
	return a.length()<b.length();
}
void check(int *tmp){
	for(int i=1;i<n;i++){
		if(!com(string(s[i]),string(s[i+1]))){
			puts("Impossible");
			exit(0);
		}
		
	}
}
int main(){
	memset(w,0x3f,sizeof w);
	for(int i=1;i<=26;i++)w[0][i]=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]);
		l[i]=strlen(s[i]);
		if(i>1){
			int j=0;
			for(;j<min(l[i],l[i-1]);j++)
				if(s[i][j]!=s[i-1][j])break;
			if(j<min(l[i],l[i-1]))
			w[s[i][j]-'a'+1][s[i-1][j]-'a'+1]=-1;
		}
	}
	for(int k=0;k<27;k++)
	for(int i=0;i<27;i++)
	for(int j=0;j<27;j++)
		w[i][j]=min(w[i][j],w[i][k]+w[k][j]);
	long long has=9,h=9;
	for(int i=0;i<27;i++)
	for(int j=0;j<27;j++)
		has=has*31+w[i][j];
	for(int k=0;k<27;k++)
	for(int i=0;i<27;i++)
	for(int j=0;j<27;j++)
		w[i][j]=min(w[i][j],w[i][k]+w[k][j]);
	for(int i=0;i<27;i++)
	for(int j=0;j<27;j++)
		h=h*31+w[i][j];
	if(has!=h)return puts("Impossible"),0;
	for(int i=1;i<=26;i++)tmp[i]=i;
	stable_sort(tmp+1,tmp+1+26,cmp);
	
	check(tmp);
	
	for(int i=1;i<=26;i++)
		putchar(tmp[i]-1+'a');
	puts("");
	return 0;
}
