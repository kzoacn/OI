#include<bits/stdc++.h>
#define ind(x) (x-pool)
using namespace std;
struct node{
	map<int,node*>go;
	node *f,*l;
	int val,id,ans,vis;
	node(node *C=0){val=id=vis=ans=0;f=l=C;}	
}*root,pool[int(200005)],*cur=pool,*null=cur++;
node* newnode(node *C){
	node *x=cur++;
	*x=node(C);return x;
}
int n,m,now;
typedef map<int,node*>::iterator Iter;
vector<int>vec[(20000)+5][2];
int anss[int(20000)+5];
int vis[int(50000)+5];
node *endd[int(50000)+5];
void insert(int id){
	int n,x;scanf("%d",&n);
	node *u=root;
	while(n--){
		scanf("%d",&x);
		if(!u->go.count(x))u->go[x]=newnode(null);
		u=u->go[x];
	}u->id=id;endd[id]=u;u->val++;
}
void bfs(){
	queue<node*>q;
	for(Iter it=root->go.begin();it!=root->go.end();it++)
		q.push(it->second),it->second->l=it->second->f=root;
	while(!q.empty()){
		node *u=q.front();q.pop();
		//cerr<<ind(u)<<": ";
		for(Iter i=u->go.begin();i!=u->go.end();i++){
			node *v=i->second,*j=u->f;q.push(v);
			//cerr<<ind(v)<<" ";
			while(j!=null&&!j->go.count(i->first))j=j->f;
			v->f=j->go.count(i->first)?j->go[i->first]:null;
			v->l=v->f->id?v->f:v->f->l;
		}//cerr<<endl;
	}
}
void print(node *j){
	//if(j->vis==now)return;
	j->ans+=j->vis!=now;j->vis=now;
	if(vis[j->id]!=now)
	anss[now]+=j->val;
	vis[j->id]=now;
	if(j->l!=null)print(j->l);
}
void find(int _x,int _y){
	node *u=root;now=_x;
	for(int i=0;i<vec[_x][_y].size();i++){
		int x=vec[_x][_y][i];
		while(u!=null&&!u->go.count(x))u=u->f;
		u=u->go.count(x)?u->go[x]:null;
		if(u->id)print(u);
		else if(u->l->id)print(u->l);
	}
}
int main(){
	root=null;null->l=null->f=null;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		int x,y;
		scanf("%d",&x);
		for(int j=1;j<=x;j++)
			scanf("%d",&y),vec[i][0].push_back(y);
		scanf("%d",&x);
		for(int j=1;j<=x;j++)
			scanf("%d",&y),vec[i][1].push_back(y);		
	}
	for(int i=1;i<=m;i++)
		insert(i);
	bfs();
	for(int i=1;i<=n;i++){
		find(i,0);
		find(i,1);
	}for(int i=1;i<=m;i++)
		printf("%d\n",endd[i]->ans);
	for(int i=1;i<=n;i++)
		printf("%d%c",anss[i]," \n"[i==n]);
	return 0;
}
