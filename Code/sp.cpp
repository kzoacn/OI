#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std; 
void Tarjan(int u){  
    dfs[u]=low[u]=++tot;  
    ins[u]=1;  
    S.push(u);  
    for(int i=0;i<G[u].size();i++){  
        edge e=edges[G[u][i]];  
        if(!dfs[e.v]){  
            Tarjan(e.v);  
            low[u]=min(low[u],low[e.v]);  
        }else if(ins[e.v]){  
            low[u]=min(low[u],dfs[e.v]);  
        }  
    }     
    if(dfs[u]==low[u]){  
        int v;  
        Scnt++;  
        do{  
            v=S.top();S.pop();  
            Belong[v]=Scnt;  
            ins[v]=0;  
        }while(u!=v);         
    }     
}  
int n,m;
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}for(int i=1;i<=n;i++)if(!dfn[i])Tarjan(i);
	
	return 0;
}
