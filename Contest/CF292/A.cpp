#include<bits/stdc++.h>
using namespace std;
char s[20];
int n;
vector<char>anss;
int main(){
	cin>>n;cin>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='0'||s[i]=='1')continue;
		int y=s[i]-'0';
		long long x=1;
		while(y>0)x*=y,y--;
		for(int j=2;j<=9;j++)
			while(x%j==0)x/=j,anss.push_back(j);
	}sort(anss.begin(),anss.end(),greater<char>());
	for(int i=0;i<anss.size();i++)
		putchar(anss[i]+'0');
	return 0;
}
