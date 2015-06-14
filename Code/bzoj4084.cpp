#include<bits/stdc++.h>
using namespace std;
int n,m,_S,_T,len;
vector<string>S,T;
char str[int(4e6+5)];
int main(){
	scanf("%d%d%d%d",&_S,&_T,&n,&m);
	len=(n+m)/2;
	for(int i=0;i<_S;i++){
		scanf("%s",str);
		S.push_back(string(str));
	}
	for(int i=0;i<_T;i++){
		scanf("%s",str);
		T.push_back(string(str));
	}
	
	return 0;
}
