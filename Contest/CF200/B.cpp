#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
char s[maxn];
int n;
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	int cur=0;
	for(int i=1;i<=n;i++){
		if(i%2){
			if(s[i]=='-')cur++;else cur--;
		}else 
			if(s[i]=='-')cur--;else cur++;			
	}
	if(cur)puts("No");
	else puts("Yes");
	return 0;
}
