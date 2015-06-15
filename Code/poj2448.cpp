#include<set>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<cstdio>
using namespace std;
const int maxn=100010;
typedef long long LL;
int pidmp[maxn],pids;
bool exist[maxn];
int n;
struct Oper{
	string ty;
	int x,y,z;
	Oper(){}
}oper[maxn];
void addop(string _ty,int _x=-1,int _y=0,int _z=0){
	static int n=0;
	n++;
	oper[n].ty=_ty;
	oper[n].x=_x;
	oper[n].y=_y;
	oper[n].z=_z;
	if(_x!=-1){pidmp[++pids]=_x;}
}
struct proc{
	int pri,mem;
	priority_queue<int>Mess;
	void clear(){pri=-1;mem=-1;while(!Mess.empty())Mess.pop();}
	int top(){return Mess.top();}
	void pop(){Mess.pop();}
	void push(int x){Mess.push(x);}
	LL calc(){
		if(Mess.empty()||pri==-1)return -1;
		return (LL)pri*Mess.top();
	}
}info[maxn];
struct byMem{
	bool operator()(int x,int y){
		return info[x].mem!=info[y].mem?info[x].mem>info[y].mem:x<y;
	}
};
struct byPri{
	bool operator()(int x,int y){
		return info[x].pri!=info[y].pri?info[x].pri>info[y].pri:x<y;
	}	
};
struct byPro{
	bool operator()(int x,int y){
		return info[x].calc()!=info[y].calc()?info[x].calc()>info[y].calc():x<y;
	}	
};
set<int,byMem>Mem;
set<int,byPri>Pri;
set<int,byPro>Pro;
void CloP(int pid);
void CreP(int pid,int mem,int pri){
	if(exist[pid]){puts("Error");return;}
	exist[pid]=1;
	info[pid].mem=mem;
	info[pid].pri=pri;
	Pro.insert(pid);
	Mem.insert(pid);
	Pri.insert(pid);
	if(mem<=0)
		CloP(pid);
}
void AM(int pid,int pri){
	if(!exist[pid]){puts("Error");return;}
	Pro.erase(pid);
	info[pid].push(pri);
	Pro.insert(pid);
}
void R(){
	if(Pro.empty()){puts("Empty");return;}
	int big=*Pro.begin();
	if(info[big].calc()==-1){puts("Empty");return;}
	printf("Run: %lld\n",info[big].calc());
	Pro.erase(big);
	info[big].pop();
	Pro.insert(big);
}
void ChaP(int pid,int pri){
	if(!exist[pid]){puts("Error");return;}
	Pri.erase(pid);
	Pro.erase(pid);	
	info[pid].pri=pri;
	Pri.insert(pid);
	Pro.insert(pid);
}
void GM(int pid,int mem){
	if(!exist[pid]){puts("Error");return;}
	Mem.erase(pid);
	info[pid].mem+=mem;
	Mem.insert(pid);
}
void FM(int pid,int mem){
	if(!exist[pid]){puts("Error");return;}
	Mem.erase(pid);
	info[pid].mem-=mem;
	Mem.insert(pid);
	if(info[pid].mem<=0)
		CloP(pid);
}
void RP(int pid){
	if(!exist[pid]){puts("Error");return;}
	if(info[pid].Mess.empty())puts("Empty");
	else {
		printf("Run Process: %d\n",info[pid].top());
		Pro.erase(pid);
		info[pid].pop();
		Pro.insert(pid);		
	}
}
void CMM(){
	if(Mem.empty())puts("Empty");
	else {
		int x=*Mem.begin();
		CloP(x);
	}
}
void CloP(int pid){
	if(!exist[pid]){puts("Error");return;}
	Mem.erase(pid);
	Pri.erase(pid);
	Pro.erase(pid);
	info[pid].clear();
	exist[pid]=0;
}
char ope[100];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",ope);
		int x,y,z;
		if(strlen(ope)==3)addop("R");
		else{
			if(ope[0]=='C'&&ope[1]=='r'){
				sscanf(ope,"CreateProcess(%d,%d,%d)",&x,&y,&z);
				addop("CreP",x,y,z);
			}else
			if(ope[0]=='A'&&ope[1]=='d'){
				sscanf(ope,"AddMessage(%d,%d)",&x,&y);
				addop("AM",x,y);
			}else
			if(ope[0]=='C'&&ope[1]=='h'){
				sscanf(ope,"ChangePriority(%d,%d)",&x,&y);
				addop("ChaP",x,y);
			}else
			if(ope[0]=='G'&&ope[1]=='e'){
				sscanf(ope,"GetMemory(%d,%d)",&x,&y);
				addop("GM",x,y);
			}else
			if(ope[0]=='F'&&ope[1]=='r'){
				sscanf(ope,"FreeMemory(%d,%d)",&x,&y);
				addop("FM",x,y);
			}else
			if(ope[0]=='R'&&ope[1]=='u'){
				sscanf(ope,"RunProcess(%d)",&x);
				addop("RP",x);
			}else
			if(ope[0]=='C'&&ope[1]=='l'){
				if(ope[5]=='M'){
					addop("CMM");
				}else{
					sscanf(ope,"CloseProcess(%d)",&x);
					addop("CloP",x);
				}
			}
		}
	}
//	sort(pidmp+1,pidmp+1+pids);
//	pids=unique(pidmp+1,pidmp+1+pids)-pidmp-1;
//	for(int i=1;i<=n;i++)if(oper[i].x!=-1)
//		oper[i].x=lower_bound(pidmp+1,pidmp+1+pids,oper[i].x)-pidmp;

	for(int i=1;i<=n;i++){
		string ty=oper[i].ty;
		int x=oper[i].x,y=oper[i].y,z=oper[i].z;
		if(ty==string("CreP"))CreP(x,y,z);
		else if(ty==string("AM"))AM(x,y);
		else if(ty==string("R"))R();
		else if(ty==string("ChaP"))ChaP(x,y);
		else if(ty==string("GM"))GM(x,y);
		else if(ty==string("FM"))FM(x,y);
		else if(ty==string("RP"))RP(x);
		else if(ty==string("CMM"))CMM();
		else if(ty==string("CloP"))CloP(x);
	}
	//getchar();
	return 0;
}
