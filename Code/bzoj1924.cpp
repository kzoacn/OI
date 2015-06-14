#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int getint(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
int X[maxn],Y[maxn],T[maxn],R,C;
map<pair<int,int>,int>M;
map<int,vector<int> >xx,yy;
vector<int>G[maxn];
vector<int>Ge[maxn];
stack<int>S;
bool ins[maxn];
int dfn[maxn],low[maxn],z,cnt,bel[maxn],w[maxn];
void dfs(int u){
	dfn[u]=low[u]=++z;ins[u]=1;S.push(u);
	for(int v,i=0;i<G[u].size();i++){
		if(!dfn[v=G[u][i]]){
			dfs(v);
			low[u]=min(low[u],low[v]);
		}else if(ins[v])low[u]=min(low[u],dfn[v]);
	}if(dfn[u]==low[u]){
		int v;cnt++;
		do{
			v=S.top();
			bel[v]=cnt;
			w[cnt]++;ins[v]=0;
			S.pop();
		}while(u!=v);
	}
}
void add(int u,int v){
//	cerr<<u<<" "<<v<<endl;
	G[u].push_back(v);
}
int F[maxn],vis[maxn];
int f(int u){
	if(vis[u])return F[u];
	int ans=w[u];vis[u]=1;
	for(int v,i=0;i<Ge[u].size();i++)
		ans=max(ans,w[u]+f(Ge[u][i]));	
	return F[u]=ans;
}
bool byX(int i,int j){return X[i]<X[j];}
bool byY(int i,int j){return Y[i]<Y[j];}
void deb(vector<int>v){
	ostream_iterator<int>out(cerr," ");
	copy(v.begin(),v.end(),out);fputs("",stderr);
}
int main(){
	int n=getint();R=getint();C=getint();
	static int xxx[maxn],yyy[maxn];
	for(int i=1;i<=n;i++){
		X[i]=getint();Y[i]=getint();T[i]=getint();
		M[pair<int,int>(X[i],Y[i])]=i;
		xx[X[i]].push_back(i);
		yy[Y[i]].push_back(i);
		xxx[++xxx[0]]=X[i];
		yyy[++yyy[0]]=Y[i];
	}
	for(int i=1;i<=n;i++)sort(xx[xxx[i]].begin(),xx[xxx[i]].end(),byY);
	for(int i=1;i<=n;i++)sort(yy[yyy[i]].begin(),yy[yyy[i]].end(),byX);	
	for(int i=1;i<=n;i++){
		if(T[i]==1){
//			deb(xx[X[i]]);
			int j;
			for(j=upper_bound(xx[X[i]].begin(),xx[X[i]].end(),i,byY)-xx[X[i]].begin();j<xx[X[i]].size()&&T[xx[X[i]][j]]!=1;j++)
				add(i,xx[X[i]][j]);
			if(j<xx[X[i]].size())add(i,xx[X[i]][j]);
			for(j=(lower_bound(xx[X[i]].begin(),xx[X[i]].end(),i,byY))-xx[X[i]].begin()-1;j>=0&&T[xx[X[i]][j]]!=1;j--)
				add(i,xx[X[i]][j]);		
			if(j>=0)add(i,xx[X[i]][j]);	
		}else
		if(T[i]==2){
			int j;
			for(j=upper_bound(yy[Y[i]].begin(),yy[Y[i]].end(),i,byX)-yy[Y[i]].begin();j<yy[Y[i]].size()&&T[yy[Y[i]][j]]!=2;j++)
				add(i,yy[Y[i]][j]);
			if(j<yy[Y[i]].size())add(i,yy[Y[i]][j]);
			for(j=(lower_bound(yy[Y[i]].begin(),yy[Y[i]].end(),i,byX))-yy[Y[i]].begin()-1;j>=0&&T[yy[Y[i]][j]]!=2;j--)
				add(i,yy[Y[i]][j]);	
			if(j>=0)add(i,yy[Y[i]][j]);	
		}else{
			const int dx[8]={0,0,1,1,1,-1,-1,-1};
			const int dy[8]={1,-1,0,1,-1,0,1,-1};
			for(int k=0;k<8;k++){
				int x=X[i]+dx[k],y=Y[i]+dy[k];
				if(x<1||x>R||y<1||y>C)continue;
				if(M.count(pair<int,int>(x,y))){
					int sec=M[pair<int,int>(x,y)];
					add(i,sec);
				}				
			}
		}
	}for(int i=1;i<=n;i++)if(!dfn[i])
	dfs(i);
	for(int i=1;i<=n;i++)for(int v,j=0;j<G[i].size();j++)if(bel[i]!=bel[v=G[i][j]])
	Ge[bel[i]].push_back(bel[v]);//,cerr<<bel[i]<<" "<<bel[v]<<endl;
	int ans=0;
	for(int i=1;i<=n;i++)
	ans=max(ans,f(i));
	cout<<ans<<endl;
	return 0;
}
