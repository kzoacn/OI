#include<bits/stdc++.h>
#include<Lrand.h>
using namespace std;Lrand R;
int n=100,m=100;
void out(int ty){
	if(ty==0){
		printf("%d\n",R.range(1,n));
	}else
	if(ty==1){
		printf("%d %d\n",R.range(1,n),R.range(1,n));
	}else
	if(ty==2){
		printf("%d %d %d\n",R.range(1,n),R.range(1,n),R.range(1,n));
	}
}
int main(){
//	freopen("sone9.in","w",stdout);
//	freopen("sone1.out","w",stdout);
	srand(_getpid());
	printf("%d %d\n",n,m);
	Lrand R;
	R.println(R.tree(n));
	R.print(R.sequence(n,10));
	printf("%d\n",1);
	while(m--){
		int op=rand()%3+1;
		//if(op==0||op>3)op=rand()%3+1;
//		if(op!=2&&op!=6&&op!=7&&op!=8&&op!=9&&op!=10)op=2;
//		if(op==9)op=1;
//		if(op==0||op==3||op==4||op==5||op==11)op=1;
//		if(op!=5&&op!=10&&op!=11)op=11;
		printf("%d ",op);
		if(op==0){
			printf("%d %d\n",R.range(1,n+1),R.range(1,10));
		}else
		if(op==1){
			printf("%d\n",R.range(1,n+1));
		}else
		if(op==2){
			printf("%d %d %d\n",R.range(1,n+1),R.range(1,n+1),R.range(0,10));
		}else
		if(op==3){
			printf("%d\n",R.range(1,n+1));
		}else
		if(op==4){
			printf("%d\n",R.range(1,n+1));
		}else
		if(op==5){
			printf("%d %d\n",R.range(1,n+1),R.range(-10,10));
		}else
		if(op==6){
			printf("%d %d %d\n",R.range(1,n+1),R.range(1,n+1),R.range(-10,10));
		}else
		if(op==7){
			printf("%d %d\n",R.range(1,n+1),R.range(1,n+1));
		}else
		if(op==8){
			printf("%d %d\n",R.range(1,n+1),R.range(1,n+1));
		}else
		if(op==9){
			printf("%d %d\n",R.range(1,n+1),R.range(1,n+1));
		}else
		if(op==10){
			printf("%d %d\n",R.range(1,n+1),R.range(1,n+1));
		}else
		if(op==11){
			printf("%d\n",R.range(1,n+1));
		}
	}
	return 0;
} 
