#include<bits/stdc++.h>
using namespace std;
vector<long long>vec;
int main(){
	vec.push_back(1);
	vec.push_back(2);
	while(vec.back()<=1e15)vec.push_back(vec[vec.size()-2]+vec.back());
	long long n;cin>>n;
	for(int i=vec.size()-1;i>=0;i--){
		if(n>=vec[i]){
			n-=vec[i];
			if(!n)cout<<vec[i]<<endl;
		}
	}
	return 0;
}
