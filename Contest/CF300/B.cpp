#include<bits/stdc++.h>
using namespace std;
vector<int>vec;
int main(){
	static int ten[10];
	ten[0]=1;
	for(int i=1;i<9;i++)ten[i]=ten[i-1]*10;
	int n;
	cin>>n;int x=n;
	static int a[7];
	int len=0;
	while(x)a[len++]=x%10,x/=10;
	vector<int>anss;
	while(n){
		int tmp=0;
		for(int i=0;i<len;i++)
		if(a[i])tmp+=ten[i],a[i]--;
		anss.push_back(tmp);
		n-=tmp;
	}cout<<anss.size()<<endl;
	for(int i=0;i<anss.size();i++)
	cout<<anss[i]<<" \n"[i+1==anss.size()];
	return 0;
}
