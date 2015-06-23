#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;cin>>s;
	for(int i=0;i<s.length();i++)
	for(int j=i;j<s.length();j++){
		string s1="";//s.substr(i,j-i+1);
		string s2=s.substr(0,i)+s.substr(j+1,s.length()-j-1);
		if(s1=="CODEFORCES"||s2=="CODEFORCES"){
			puts("YES");return 0;
		}
	}puts("NO");
	return 0;
}
