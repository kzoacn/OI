#include<cstdio> 
#include<cstdlib>
#include<algorithm>
#include<queue>
#include<ctime>
int start = clock();
typedef long long ll;
const int MOD = 1E9+7;
const int N = 1E6+100;
const int LOGN = 51;
const int TN = N*LOGN;
using namespace std;
int scan(){
	char cc=' ';int re=0,fh=1;while(cc==' '||cc=='\r'||cc=='\n')cc=getchar();
	if(cc=='+')cc=getchar(),fh=1;if(cc=='-')cc=getchar(),fh=-1;
	while('0'<=cc&&cc<='9'){re=re*10+cc-'0';cc=getchar();}return re*fh;
}
struct Point{
	Point(){next=NULL;}
	Point*next;int d;
	void push(int);
}point[N],*cur[N];
queue<Point*>pupa;
Point *newPoint(){
	if(pupa.empty()) return new Point;
	Point *r = pupa.front();pupa.pop();
	if(r->next)pupa.push(r->next);
	*r = Point();return r;
}
void Point::push(int a){
	Point *l = newPoint();
	l->d = a;
	l->next=next;next=l;
}
int n,m,fa[N],dlist[N*2],pos[N][2],deep[N],ans;
void dfs(){
	int now = 1;
	deep[now] = 1;
	for(int i=1;i<=n;i++)cur[i] = point[i].next;
	while(now){
		if(!pos[now][0]){
			pos[now][0] = ++dlist[0];
			dlist[dlist[0]] = now;
		}
		Point *&i = cur[now];
		if(i){
			deep[i->d] = deep[now] + 1;
			now = i->d;
			i = i->next;
		}else{
			pos[now][1] = ++dlist[0];
			dlist[dlist[0]] = -now;
			now = fa[now];
		}
	}
}
typedef pair<int,int> Data;
Data last[N];
int I,COL,T;
namespace STree{
	int ROOT,lson[TN],rson[TN],tt[TN];
	Data tree[TN];
	inline int Newp(){
		++T;
		if(T > TN)system("title ERROR");
		lson[T] = rson[T] = tt[T] = 0;
		tree[T] = Data(0,1);
		return T;
	}
	void Set2(int bl,int br,int &ro,int l=1,int r=dlist[0]){
		if(!ro)ro = Newp();
		if(bl <= l && r <= br){
			tree[ro] = Data(I,COL);
			return;
		}
		int mid = (l+r)/2;
		if(bl <= mid)Set2(bl,br,lson[ro],l,mid);
		if(mid+1 <= br)Set2(bl,br,rson[ro],mid+1,r);
	}
	void Set(int al,int ar,int bl,int br,int &ro=ROOT,int l=1,int r=n){
		if(!ro)ro = Newp();
		if(al <= l && r <= ar){
			Set2(bl,br,tt[ro]);
			return;
		}
		int mid = (l+r)/2;
		if(al <= mid)Set(al,ar,bl,br,lson[ro],l,mid);
		if(mid+1 <= ar)Set(al,ar,bl,br,rson[ro],mid+1,r);
	}
	Data NOW;
	void Ask2(int b,int ro,int l=1,int r=dlist[0]){
		if(tree[ro] > NOW) NOW = tree[ro];
		if(l==r)return;
		int mid = (l+r)/2;
		if(b <= mid)Ask2(b,lson[ro],l,mid);
		else Ask2(b,rson[ro],mid+1,r);
	}
	void Ask(int a,int b,int ro=ROOT,int l=1,int r=n){
		Ask2(b,tt[ro]);
		if(l==r)return;
		int mid = (l+r)/2;
		if(a <= mid)Ask(a,b,lson[ro],l,mid);
		else Ask(a,b,rson[ro],mid+1,r);
	}
	void reBuild(){
		int i,j;
		for(i=1;i<=n;i++){
			NOW = last[i];
			Ask(deep[i],pos[i][0]);
			last[i] = NOW;
		}
		T=0;ROOT=0;
	}
}
void clear(){
	for(int i=1;i<=n;i++){
		if(point[i].next){
			pupa.push(point[i].next);
			point[i].next=NULL;
		}
		fa[i]=deep[i]=pos[i][0]=pos[i][1]=0;
	}
	T=ans=dlist[0]=STree::ROOT=0;
}
inline void tset(int a,int b,int c,int d){
	return;
	char s[100];
	sprintf(s,"title %d/%d %d/%d Use:[%d/%d] %.3f",a,b,c,d,T/1000000,TN/1000000,(clock()-start)*1./CLOCKS_PER_SEC);
	system(s);
}
int main(){
	int i,j,a,b,c;
	int nn = scan(),sn=nn;
	STree::tree[0] = Data(0,1);
	while(nn--){
		n = scan();scan();m = scan();
		for(i=2;i<=n;i++){
			fa[i]=scan();
			point[fa[i]].push(i);
		}
		for(i=1;i<=n;i++) last[i]=Data(0,1);
		dfs();
		for(i=1;i<=m;i++){
			if(i % 10000 == 0)
				tset(sn-nn,sn,i,m);
			using namespace STree;
			a=scan();b=scan();c=scan();
			if(c){//Set
				COL = c;
				I = i;
				Set(deep[a],deep[a]+b,pos[a][0],pos[a][1]-1);
			}else{//Query
				NOW = last[a];
				Ask(deep[a],pos[a][0]);
				ans = (ans + (ll)i * NOW.second)%MOD;
//				printf("%d\n",NOW.second);
			}
			if(T/1000000 > 50){
				reBuild();
			}
		}
		printf("%d\n",ans);
		clear();
	}
//	printf("%.3f\n",(clock()-start)*1./CLOCKS_PER_SEC);
	return 0;	
}
