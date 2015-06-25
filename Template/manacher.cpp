#include<bits/stdc++.h>
using namespace std;
int main(){
	char c=getchar();s[0]='+';s[++n]='#';
	while(isalpha(c))str[++m]=c,s[++n]=c,s[++n]='#',c=getchar();s[++n]='-';
	f[1]=1;
	for(int i=2,k=1;i<=n;i++){
		if(f[k]+k>i)f[i]=min(f[k+k-i],f[k]+k-i);else f[i]=1;
		while(s[i+f[i]]==s[i-f[i]])f[i]++;
		if(f[k]+k<f[i]+i)k=i;		
	}
	return 0;
}
