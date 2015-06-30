#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
string ran(int l){
	string s;
	while(l--)s.push_back(rand()%3+'a');
	return s;
}
int mp[233];
string tran(string s){
	for(int i=0;i<s.length();i++)
		s[i]=mp[s[i]];
	return s;
}
int main(){
	srand(time(0)^getpid());
	for(char i='a';i<='z';i++)mp[i]=i;
	random_shuffle(mp+'a',mp+'z'+1);
	int n=100;
	vector<string>vec;
	for(int i=0;i<n;i++)vec.push_back(ran(rand()%100+1));
	sort(vec.begin(),vec.end());
	vec.erase(unique(vec.begin(),vec.end()),vec.end());
	for(int i=0;i<vec.size();i++)vec[i]=tran(vec[i]);
	printf("%d\n",(int)vec.size());
	for(int i=0;i<vec.size();i++)
		cout<<vec[i]<<endl;
	return 0;
}
