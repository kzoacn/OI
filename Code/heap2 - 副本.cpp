#include<bits/stdc++.h>
using namespace std;
int n,m;
priority_queue<int,vector<int>,greater<int> >q;
int main(){
	scanf("%d%d",&n,&m);
    while(m--){
		int op;scanf("%d",&op);
		if(op==1){
			int x;scanf("%d",&x);
			q.push(x);
		}else
		if(op==2){
			q.pop();
		}else printf("%d\n",q.top());	
	}cerr<<clock()/double(CLOCKS_PER_SEC)<<endl;
	return 0;
}
