#include<bits/stdc++.h>
using namespace std;
int n;
map<deque<int>,int>M;
deque<int>one;
int dfs(deque<int>dq){
	if(dq.size()==1)return M[dq]=!!dq[0];
	if(M.count(dq))return M[dq];
	deque<int>tmp;
	for(int i=1;i<=dq.front();i++){
		tmp=dq;tmp[0]-=i;
		while(!tmp.front())tmp.pop_front();
		if(!dfs(tmp))return M[dq]=1;
	}
	for(int i=1;i<=dq.back();i++){
		tmp=dq;tmp[tmp.size()-1]-=i;
		while(!tmp.back())tmp.pop_back();
		if(!dfs(tmp))return M[dq]=1;
	}
	return M[dq]=0;
}
int main(){
	freopen("tab.txt","w",stdout);
	deque<int>dq;M[dq]=0;


	one.push_back(1);
	one.push_back(1);
	dq.resize(4);	
	for(dq[0]=1;dq[0]<=5;dq[0]++)
	for(dq[1]=1;dq[1]<=5;dq[1]++)
	for(dq[2]=1;dq[2]<=5;dq[2]++)
	for(dq[3]=1;dq[3]<=5;dq[3]++)
	dfs(dq);
	for(map<deque<int>,int>::iterator it=M.begin();it!=M.end();it++)
	if(1){
		for(int i=0;i<it->first.size();i++)cout<<it->first[i]<<" ";
		cout<<"\t"<<it->second<<endl;
	}

	return 0;
}
