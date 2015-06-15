#include<bits/stdc++.h>
using namespace std;
int n;
char s[int(2e6)];
string s1,s2;
string sol(char *s){
	int n=strlen(s);
	int i=0,j=1,k=0,p;
	while(i<n&&j<n&&k<n){
		int t=s[(i+k)%n]-s[(j+k)%n];
		if(t==0)k++;
		else if(t<0)j+=k+1,k=0;
		else i+=k+1,k=0;
		if(i==j)j++;
	}p=min(i,j);
	string S;
	for(int i=p;i<p+n;i++)S.push_back(s[i%n]);
	return S;
}
int main(){
//	scanf("%d",&n);
	scanf("%s",s);
	s1=sol(s);
	scanf("%s",s);
	s2=sol(s);
	if(s1!=s2)puts("No");
	else printf("Yes\n%s\n",s1.c_str());
	return 0;
}
