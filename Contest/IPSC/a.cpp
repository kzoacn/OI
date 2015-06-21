#include<bits/stdc++.h>
using namespace std;
void sol(){
	char s[20];
	scanf("%s",s);
	int n=strlen(s);
	sort(s,s+n,greater<char>());
	long long a,b;
	b=s[n-1]-'0';s[n-1]=0;
	sscanf(s,"%lld",&a);
	cout<<a+b<<endl;
}
int main(){
	freopen("a2.in","r",stdin);
	freopen("a2.out","w",stdout);
	int T;scanf("%d",&T);
	while(T--)sol();
}
